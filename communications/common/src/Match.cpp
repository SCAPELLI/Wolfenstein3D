
#include "../include/Match.h"
#include "../include/Socket.h"
#include "../include/CommunicationChannel.h"

Match::Match(int matchId, int levelId, int maximumNumberOfPlayers,
             int adminUserId, str adminUserName, Socket* adminUserSocket):
             matchId(matchId),levelId(levelId),
             maximumNumberOfPlayers(maximumNumberOfPlayers),
             adminUserId(adminUserId),
             matchStarted(false) {
    addUser(adminUserName, adminUserId, adminUserSocket);
    }
void Match::addUser(str userName, int userId, Socket* userSocket) {
    users[userName] = userId;
    usersSockets[userId] = userSocket;
}

int Match::getActualNumberOfUsers() const {
    return users.size();
}
bool Match::sameIdAs(int aMatchId) const {
    return matchId == aMatchId;
}
bool Match::isNotFull() const {
    return maximumNumberOfPlayers > users.size();
}
bool Match::userIsPartOfTheMatch (str userName, int userId) const {
    auto it = users.find(userName);
    if (it != users.end())
        return it->second == userId;
    else
        return false;
}
bool Match::userIsAdmin(int userId) const {
    return userId == adminUserId;
}
void Match::removeUser(str userName, int userId) {
    if (userIsPartOfTheMatch(userName, userId))
        users.erase(userName);
    if (usersSockets.find(userId) != usersSockets.end())
        usersSockets.erase(userId);
}
bool Match::notStarted() const {
    return !matchStarted;
}
MatchInfo Match::getMatchInfo() const {
    return {matchId, levelId, maximumNumberOfPlayers, (int)users.size()};
}
void Match::run() {
    for (auto& user: users)
        CommunicationChannel::sendMatchStartedSignal(usersSockets[user.second]);

    std::cout<< "se ejecutó una partida"<<std::endl;
}

