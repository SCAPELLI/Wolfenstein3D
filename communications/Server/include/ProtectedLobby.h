#ifndef PROTECTEDLOBBY_H
#define PROTECTEDLOBBY_H

#include <string>
#include <vector>
#include <map>
#include "Match.h"

typedef std::string str;

class ProtectedLobby {
    std::vector<Match> matches;
    std::map<str, int> users;
    int reference;
public:
    ProtectedLobby();
    int addUser(str& userName);
    str getUserName(int userId);
    std::vector<Match> getMatches();
    int createANewMatch(int levelId, int maximumNumberOfPlayers, int adminId);
    int addUserToMatch(int matchId, int userId);
    void removeUser(int userId);
    int numberOfUsersInMatch(int matchId);
    int cancelMatch(int matchId);
};
#endif
