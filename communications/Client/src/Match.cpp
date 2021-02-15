#include "../include/Match.h"

Match::Match(int matchId, int levelId, int maximumNumberOfPlayers, int adminUserId, str adminUserName):
            matchId(matchId),levelId(levelId),
            maximumNumberOfPlayers(maximumNumberOfPlayers),
            adminUserId(adminUserId) {
        users[adminUserName] = adminUserId;
    }
void Match::addUser(str userName, int userId) {
    users[userName] = userId;
}
int Match::getMatchId() const {
    return matchId;
}
int Match::getLevelId() const {
    return levelId;
}
int Match::getMaximumNumberOfPlayers() const {
    return maximumNumberOfPlayers;
}
int Match::getActualNumberOfUsers() const {
    return users.size();
}
bool Match::sameIdAs(int aMatchId) const {
    return matchId == aMatchId;
}
bool Match::isNoFull() const {
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
}

