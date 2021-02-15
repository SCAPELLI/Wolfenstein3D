#ifndef MATCH_H
#define MATCH_H

#include <map>

typedef std::string str;

class Match {
    std::map<str, int> users;
    int maximumNumberOfPlayers;
    int matchId;
    int levelId;
    int adminUserId;
public:
    Match(int matchId, int levelId, int maximumNumberOfPlayers, int adminUserId, str adminUserName);
    void addUser(str userName, int userId);
    int getMatchId() const;
    int getLevelId() const;
    int getMaximumNumberOfPlayers() const;
    int getActualNumberOfUsers() const;
    bool sameIdAs(int aMatchId) const;
    bool isNoFull() const;
    bool userIsPartOfTheMatch (str userName, int userId) const;
    bool userIsAdmin(int userId) const;
    void removeUser(str userName, int userId);
};

#endif
