#include <algorithm>
#include <unistd.h>
#include "../include/ProtectedLobby.h"

ProtectedLobby::ProtectedLobby(char* configPath): reference(0), configPath(configPath) {};

int ProtectedLobby::addUser(str& userName) {
    std::unique_lock<std::mutex> lock(m);

    int userId = -1;
    if (userName.empty()) return userId;
    if (users[userName] == 0) {
        userId = (int)users.size();
        users[userName] = userId;
    }
    return userId;
}

//metodo privado, no necesita lock
str ProtectedLobby::getUserName(int userId) {
    auto it = std::find_if(users.begin(),users.end(),
                           [&](const std::pair<str, int>& user) {return user.second == userId; });

    if (it != users.end())
        return it->first;
    else
        return "";
}

std::vector<MatchInfo> ProtectedLobby::getMatchesInfo() {
    std::unique_lock<std::mutex> lock(m);

    std::vector<MatchInfo> matchesInfo;
    for (Match& match: matches)
        if (match.notStarted() and match.notFinished() and match.notCancelled())
            matchesInfo.emplace_back(match.getMatchInfo());
    return matchesInfo;
}
int ProtectedLobby::createANewMatch(int levelId, int maximumNumberOfPlayers, int adminId, Socket* adminSocket) {
    std::unique_lock<std::mutex> lock(m);

    if (maximumNumberOfPlayers < 1)
        return -1;
    else {
        ++reference;
        str adminUserName = getUserName(adminId);
        matches.emplace_back(reference, levelId, maximumNumberOfPlayers, adminId, adminUserName, adminSocket, this, configPath);
        return reference;
    }
}
int ProtectedLobby::addUserToMatch(int matchId, int userId, Socket* userSocket) {
    std::unique_lock<std::mutex> lock(m);

    auto it = std::find_if(matches.begin(), matches.end(),
                           [&] (const Match& match) { return match.sameIdAs(matchId);});

    if (!(it != matches.end() and it->isNotFull() and it->notStarted() and it->notCancelled()))
        return -1;
    it->addUser(getUserName(userId), userId, userSocket);

    while (it->notFinished() and it->notCancelled() and it->userIsPartOfTheMatch(userId))
        cv.wait(lock);
    joinMatchesFinished();
    if (it->notCancelled()) return 0;
    else return -1;
}

void ProtectedLobby::removeUser(int userId) {
    std::unique_lock<std::mutex> lock(m);

    str userName = getUserName(userId);
    if (userName.empty()) return;

    users.erase(userName);

    auto it = std::find_if(
            matches.begin(), matches.end(),
            [&] (const Match& match) { return match.userIsPartOfTheMatch(userName, userId);});

    if (it == matches.end()) return;

    if (it->userIsAdmin(userId)) {
        it->cancelMatch();
        cv.notify_all();
    } else {
        it->removeUser(userName, userId);
    }
}
int ProtectedLobby::numberOfUsersInMatch(int matchId) {
    std::unique_lock<std::mutex> lock(m);

    auto it = std::find_if(
            matches.begin(), matches.end(),
            [&] (const Match& match) { return match.sameIdAs(matchId);});
    if (it == matches.end()) return -1;

    return it->getActualNumberOfUsers();
}

//Solo se puede cancelar un match que aun no comenzo
int ProtectedLobby::cancelMatch(int matchId) {
    std::unique_lock<std::mutex> lock(m);

    auto it = std::find_if(
            matches.begin(), matches.end(),
            [&] (const Match& match) { return match.sameIdAs(matchId);});
    if (it == matches.end()) return -1;
    if (it->notStarted()) {
        it->cancelMatch();
        cv.notify_all();
    }
    return 0;
}

int ProtectedLobby::startMatch(int matchId) {
    std::unique_lock<std::mutex> lock(m);

    auto it = std::find_if(
            matches.begin(), matches.end(),
            [&] (const Match& match) { return match.sameIdAs(matchId);});
    if (it == matches.end()) return -1;
    it->start();


    while (it->notFinished() and it->userIsPartOfTheMatch(it->adminUserId))
        cv.wait(lock);
    cv.notify_all();
    joinMatchesFinished();
    return 0;
}

void ProtectedLobby::notifyAll() {
    //std::unique_lock<std::mutex> lock(m);
    cv.notify_all();
}

void ProtectedLobby::joinMatchesFinished() {
    for(auto& match: matches)
        if (match.joinable() and !(match.notFinished()))
            match.join();
}

void ProtectedLobby::JoinMatches() {
    std::unique_lock<std::mutex> lock(m);
    for(auto& match: matches)
        if (match.joinable())
            match.join();
}