#ifndef MATCH_H
#define MATCH_H

#include <map>
#include "../../common/include/Thread.h"
#include "../../common/include/MatchInfo.h"
/* Thread donde se desarrolla el juego y se intercambia información*/
typedef std::string str;

class Socket;
class Event;
class ProtectedLobby;

class Match: public Thread {
    bool matchStarted;
    bool matchFinished;
    bool matchCancelled;
    std::map<str, int> users;
    std::map<int, Socket*> usersSockets;
    int maximumNumberOfPlayers;
    int matchId;
    int levelId;
    ProtectedLobby* lobby;
    char* configPath;
public:
    int adminUserId;

    Match(int matchId, int levelId, int maximumNumberOfPlayers,
          int adminUserId, str adminUserName, Socket* adminUserSocket, ProtectedLobby* lobby, char* configPath);

    Match(const Match& anotherMatch) = delete;
    Match& operator=(const Match& anotherMatch) = delete;

    void addUser(str userName, int userId, Socket* userSocket);
    bool notStarted() const;
    MatchInfo getMatchInfo() const;
    int getActualNumberOfUsers() const;
    bool sameIdAs(int aMatchId) const;
    bool isNotFull() const;
    bool userIsPartOfTheMatch (str userName, int userId) const;
    bool userIsAdmin(int userId) const;
    void removeUser(str userName, int userId);
    void cancelMatch();
    bool notFinished() const;
    bool notCancelled() const;
    void run() override;
    void removeUser(Event* quitEvent);
    bool userIsPartOfTheMatch(int userId);
};

#endif
