#include <algorithm>
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
std::vector<Match> ProtectedLobby::getMatches() {
    return matches;
}
int ProtectedLobby::createANewMatch(int levelId, int maximumNumberOfPlayers, int adminId) {
    // queda pendiente la logica de validacion de nivel existente
    // en esta primer version solo es valido el nivel 1

    if ((maximumNumberOfPlayers < 1) or (levelId != 1))
        return -1;
    else {
        ++reference;
        str adminUserName = getUserName(adminId);
        matches.emplace_back(reference, levelId, maximumNumberOfPlayers, adminId, adminUserName);
        return reference;
    }
}
int ProtectedLobby::addUserToMatch(int matchId, int userId) {
    auto it = std::find_if(matches.begin(), matches.end(),
                           [&] (const Match& match) { return match.sameIdAs(matchId);});
    if (it != matches.end() and it->isNoFull()) {
        it->addUser(getUserName(userId), userId);
        return 0;
    } else {
        return -1;
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
    matches.erase(it);
    return 0;
}
