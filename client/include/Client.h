#ifndef MENU_CLIENT_H
#define MENU_CLIENT_H


#include <string>
#include <vector>
#include "common/include/MatchInfo.h"
#include "common/include/Socket.h"

class CommunicationChannelClient;

class Client {
    Socket userSocket;
    CommunicationChannelClient* channel;
    int userId;
    int matchId;
    int levelId;
    int maximumNumberOfPlayers;

public:
        Client();
        ~Client();
        bool tryToConnect(std::string port, std::string domain);
        bool tryToSubmitUsername(std::string userName);
        bool tryToJoin(int matchId);
        std::vector<MatchInfo> requestMatches();
        bool tryToCreateAMatch(int level, int maxPlayer);
        int getLevel();
        int getActualPlayers();
        int getMaxPlayers();
        bool tryToCancelMatch();
        bool tryToStartMatch();
        void playMatch();
};


#endif //MENU_CLIENT_H
