#ifndef PROTECTEDLOBBY_H
#define PROTECTEDLOBBY_H

#include <string>
#include <map>
#include <list>
#include <vector>
#include "../include/Match.h"
#include "../include/MatchInfo.h"

typedef std::string str;

class Socket;

class ProtectedLobby {
    std::list<Match> matches; //partidas que aun no iniciaron
    std::map<str, int> users;
    int reference;
public:
    ProtectedLobby();
    int addUser(str& userName);
    str getUserName(int userId);
    std::vector<MatchInfo> getMatchesInfo();
    int createANewMatch(int levelId, int maximumNumberOfPlayers, int adminId, Socket* adminSocket);
    int addUserToMatch(int matchId, int userId, Socket* userSocket);
    void removeUser(int userId);
    int numberOfUsersInMatch(int matchId);
    int cancelMatch(int matchId);
    int startMatch(int matchId);
};
#endif
