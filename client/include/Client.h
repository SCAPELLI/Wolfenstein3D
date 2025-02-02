#ifndef MENU_CLIENT_H
#define MENU_CLIENT_H


#include <string>
#include <vector>
#include <common/include/BlockingEventsQueue.h>
#include "common/include/MatchInfo.h"
#include "common/include/Socket.h"
#include <map>
#include <list>

class CommunicationChannelClient;
class ScreenManager;
class CreateMapEvent;

class Client {
    Socket userSocket;
    CommunicationChannelClient* channel;
    int userId;
    int matchId;
    int levelId;
    int maximumNumberOfPlayers;
    bool gameIsPlaying;
    ScreenManager *screenManager;
    std::vector<std::vector<int>> generateMap(CreateMapEvent* start);
    bool receiveMap(std::list<Message>& messages, CGame& game);
public:
    bool matchStarted;
    std::map<std::string, std::vector<int>> highscores;
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
        void catchEvents(BlockingEventsQueue &senderQueue);
        void setScreenManager(ScreenManager *screenManager);
};


#endif //MENU_CLIENT_H
