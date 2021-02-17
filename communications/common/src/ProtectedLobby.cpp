#include <algorithm>
#include <unistd.h>
#include "../include/ProtectedLobby.h"

ProtectedLobby::ProtectedLobby(): reference(0) {};

int ProtectedLobby::addUser(str& userName) {
    int userId = -1;
    if (users[userName] == 0) {
        userId = (int)users.size();
        users[userName] = userId;
    }
    return userId;
}
str ProtectedLobby::getUserName(int userId) {
    auto it = std::find_if(users.begin(),users.end(),
                           [&](const std::pair<str, int>& user) {return user.second == userId; });

    if (it != users.end())
        return it->first;
    else
        return "";
}
std::vector<MatchInfo> ProtectedLobby::getMatchesInfo() {
    std::vector<MatchInfo> matchesInfo;
    for (Match& match: matches)
        if (match.notStarted())
            matchesInfo.emplace_back(match.getMatchInfo());
    return matchesInfo;
}
int ProtectedLobby::createANewMatch(int levelId, int maximumNumberOfPlayers, int adminId, Socket* adminSocket) {
    // queda pendiente la logica de validacion de nivel existente
    // en esta primer version solo es valido el nivel 1

    if ((maximumNumberOfPlayers < 1) or (levelId != 1))
        return -1;
    else {
        ++reference;
        str adminUserName = getUserName(adminId);
        matches.emplace_back(reference, levelId, maximumNumberOfPlayers, adminId, adminUserName, adminSocket);
        return reference;
    }
}
int ProtectedLobby::addUserToMatch(int matchId, int userId, Socket* userSocket) {
    auto it = std::find_if(matches.begin(), matches.end(),
                           [&] (const Match& match) { return match.sameIdAs(matchId);});
    if (!(it != matches.end() and it->isNotFull() and it->notStarted())) {
        return -1;
    } else {
        it->addUser(getUserName(userId), userId, userSocket);
        while (std::find_if(matches.begin(), matches.end(),
                            [&] (const Match& match) { return match.sameIdAs(matchId);}) != matches.end())
            usleep(500000);
        return 0;
    }
}
void ProtectedLobby::removeUser(int userId) {
    str userName = getUserName(userId);
    if (userName.empty()) return;

    users.erase(userName);

    auto it = std::find_if(
            matches.begin(), matches.end(),
            [&] (const Match& match) { return match.userIsPartOfTheMatch(userName, userId);});

    if (it == matches.end()) return;

    if (it->userIsAdmin(userId))
        matches.erase(it);
    else
        it->removeUser(userName, userId);
}
int ProtectedLobby::numberOfUsersInMatch(int matchId) {
    auto it = std::find_if(
            matches.begin(), matches.end(),
            [&] (const Match& match) { return match.sameIdAs(matchId);});
    if (it == matches.end()) return -1;

    return it->getActualNumberOfUsers();
}
int ProtectedLobby::cancelMatch(int matchId) {
    auto it = std::find_if(
            matches.begin(), matches.end(),
            [&] (const Match& match) { return match.sameIdAs(matchId);});
    if (it == matches.end()) return -1;
    if (it->notStarted())
        matches.erase(it);
    return 0;
}

int ProtectedLobby::startMatch(int matchId) {
    auto it = std::find_if(
            matches.begin(), matches.end(),
            [&] (const Match& match) { return match.sameIdAs(matchId);});
    if (it == matches.end()) return -1;
    it->start();
    //cuando agreges el mutex aca hay que desbloquear, sino nunca se va a habilitar el lobby
    it->join();
    matches.erase(it);
    return 0;
}
