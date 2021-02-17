#ifndef MENU_CLIENT_H
#define MENU_CLIENT_H


#include <string>
#include <vector>
#include "../../common/MatchInfo.h"

class Client {
    public:
        Client();
        ~Client();
        bool tryToConnect(std::string port, std::string domain);
        bool tryToSubmitUsername(std::string nickname);
        bool tryToJoin(int matchId);
        std::vector<MatchInfo> requestMatches();
        bool tryToCreateAMatch(int level, int maxPlayer);
        int getLevel();
        int getActualPlayers();
        int getMaxPlayers();
};


#endif //MENU_CLIENT_H
