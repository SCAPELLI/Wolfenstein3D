#ifndef PROTECTEDLOBBY_H
#define PROTECTEDLOBBY_H

#include <string>
#include <map>
#include <list>
#include <vector>

#include <condition_variable>
#include <mutex>
#include "../include/Match.h"
#include "../../common/include/MatchInfo.h"

typedef std::string str;

class Socket;



class ProtectedLobby {
    std::list<Match> matches;
    std::map<str, int> users;

    std::condition_variable cv;
    std::mutex m;

    int reference;
    str getUserName(int userId);
    void joinMatchesFinished();
    char* configPath;
public:
    ProtectedLobby(char* configPath);

    ProtectedLobby (const ProtectedLobby& anotherLobby) = delete;
    ProtectedLobby& operator=(const ProtectedLobby& anotherLobby) = delete;

    int addUser(str& userName);
    std::vector<MatchInfo> getMatchesInfo();
    int createANewMatch(int levelId, int maximumNumberOfPlayers, int adminId, Socket* adminSocket);
    int addUserToMatch(int matchId, int userId, Socket* userSocket);
    void removeUser(int userId);
    int numberOfUsersInMatch(int matchId);
    int cancelMatch(int matchId);
    int startMatch(int matchId);
    void notifyAll();
    void JoinMatches();
};
#endif
