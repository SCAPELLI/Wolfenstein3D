#ifndef MATCH_H
#define MATCH_H

#include <map>
#include "../include/Thread.h"
#include "../include/MatchInfo.h"

typedef std::string str;

class Socket;

class Match: public Thread {
    bool matchStarted;
    bool matchFinished;
    bool matchCancelled;
    std::map<str, int> users;
    std::map<int, Socket*> usersSockets;
    int maximumNumberOfPlayers;
    int matchId;
    int levelId;
    int adminUserId;
public:
    Match(int matchId, int levelId, int maximumNumberOfPlayers,
          int adminUserId, str adminUserName, Socket* adminUserSocket);

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
};

#endif
