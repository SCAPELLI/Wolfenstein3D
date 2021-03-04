#include <iostream>
#include <common/include/EventSerializer.h>
#include "client/include/Client.h"
#include "client/include/TCPClient.h"
#include "client/include/CommunicationChannelClient.h"
#include "common/include/BlockingEventsQueue.h"
#include "common/include/ProtectedEventsQueue.h"
#include "../../common/ServerEvents/CreateMapEvent.h"
#include "../../server/include/ReceiverThread.h"
#include "../../server/include/SenderThread.h"
#include "../../common/include/Message.h"
#include "common/include/EventSerializer.h"
#include "common/include/QuitEvent.h"
#include "client/include/ScreenManager.h"

#define FOV 0.66

Client::Client(): userId(-1), matchId(-1), maximumNumberOfPlayers(-1), levelId(-1), gameIsPlaying(false), matchStarted(false) {
        channel = new CommunicationChannelClient(userSocket);
}
Client::~Client() {
    delete channel;
}

bool Client::tryToConnect(std::string port, std::string domain) {
    try {
        //userSocket = std::move(TCPClient::getClientSocket(domain.c_str(), port.c_str()));
        userSocket = std::move(TCPClient::getClientSocket("localhost", "7777"));
        return true;
    } catch (const std::exception& error) {
        return false;
    }
}

bool Client::tryToSubmitUsername(std::string userName) {

    channel->sendUserNameSubmit(userName);
    userId = channel->receiveClientIdFromServer();
    if (userId == -1) return false;
    else return true;
}

bool Client::tryToJoin(int matchId) {
    channel->sendRequestOfJoiningAMatch(matchId, userId);
    this->matchId = matchId;
    int response = channel->receiveResponseOfJoiningAMatch();
    if (response == -1) {
        return false;
    } else {
        this->screenManager->close();
        playMatch();
        return true;
    }
}

std::vector<MatchInfo> Client::requestMatches() {
    channel->sendRequestOfAvailableMatches();
    std::vector<MatchInfo> matches = channel->receiveListOfMatches();

    return matches;
}

bool Client::tryToCreateAMatch(int level, int maxPlayer) {
    levelId = level;
    maximumNumberOfPlayers = maxPlayer;
    if (maximumNumberOfPlayers>999) return false;
    channel->sendRequestOfMatchCreation(level, maxPlayer, userId);
    matchId = channel->receiveResponseToRequestOfMatchCreation();
    if (matchId == -1) return false;
    else return true;
}

int Client::getLevel() {
    return levelId;
}

int Client::getActualPlayers() {
    channel->sendRequestOfNumberOfUsersInMatch(matchId);
    return channel->receiveResponseOfNumberOfMatches();
}

int Client::getMaxPlayers() {
    return maximumNumberOfPlayers;
}

bool Client::tryToCancelMatch() {
    channel->sendRequestOfMatchCancellation(matchId);
    int response = channel->receiveResponseOfMatchCancellation();
    if (response == -1) {
        return false;
    } else {
        maximumNumberOfPlayers = -1;
        levelId = -1;
        return true;
    }
}
bool Client::tryToStartMatch() {
    channel->sendRequestOfStartMatch(matchId);
    if (channel->receiveResponseToRequestOfStartMatch() != -1) {
        this->screenManager->close();
        playMatch();
        return true;
    } else {
        return false;
    }
}

void Client::catchEvents(BlockingEventsQueue& senderQueue){
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)){
        Event event(sdlEvent, userId);

        EventSerializer::serialize(event);
        Message msg(EventSerializer::serialize(event));
        //if(event.thisIsTheQuitEvent()) gameIsPlaying = false;
        if(msg.getMessage() != "")
            senderQueue.push(msg);
    }
}

void Client::playMatch() {
    matchStarted = true;
    BlockingEventsQueue senderQueue;
    ProtectedEventsQueue receiverQueue;

    ReceiverThread r(&userSocket, &receiverQueue, userId);
    r.start();

    bool hasStarted = false;
    while (!hasStarted){
        if (!receiverQueue.empty()){
            hasStarted = true;
        }
    }
    //Event event = std::move(receiverQueue.pop());
    SDL_Delay(2000); // este delay deberia ser reemplazado por un startgameevent
    std::list<Message> messageEvents = receiverQueue.popAll();
    Event event = std::move(EventSerializer::deserialize(messageEvents.front().getMessage()));
    messageEvents.pop_front(); //ojo si sacas muchos elementos con el popAll acá, hay que procesarlos en algun lado
                                //solo agrego las tres lineas de arriba como ejemplo de como quedo para desencolar.


    CreateMapEvent* start = (CreateMapEvent*) (event).event;
    double spawnPointX = start->startingLocations[userId].first;
    double spawnPointY = start->startingLocations[userId].second;

    std::vector<std::vector<int>> map;
    for (int i = 0; i <= start->height; i++){
        std::vector<int> row;
        for (int j = 0; j <= start->width; j++){
            row.push_back(0);
        }
        map.push_back(row);
    }

    CGame game(spawnPointX, spawnPointY, FOV, map, userId, gameIsPlaying);
    for (auto it = start->startingLocations.begin(); it != start->startingLocations.end(); ++it){
        if (it->first == userId) continue;
        game.spawnEnemy(it->first, Vector(start->startingLocations[it->first].first,
                                          start->startingLocations[it->first].second));
    }

    SenderThread s(&userSocket, &senderQueue, userId);
    s.start();
    gameIsPlaying = true;
    while (gameIsPlaying) {

        catchEvents(senderQueue);
        while (!messageEvents.empty()) {
            Event event1 = std::move(EventSerializer::deserialize(messageEvents.front().getMessage()));
            messageEvents.pop_front();
            if (event1.thisIsTheQuitEvent()) {
                gameIsPlaying = ((QuitEvent*)(event1.event))->playerId != userId;
                this->highscores = ((QuitEvent*)(event1.event))->highscore;
            } else {
                event1.runHandler(game);
            }
        }
        messageEvents = receiverQueue.popAll();
        game.draw();
        game.playSounds();
        game.advanceTime();
        SDL_Delay(33);
    }
    QuitEvent quit(userId);
    Event finalEvent(&quit, QuitEventType);
    Message msg(EventSerializer::serialize(finalEvent));
    senderQueue.push(msg);
    s.join();
    r.join();
    if (this->highscores.empty())
        this->highscores = game.highscores;
}

void Client::setScreenManager(ScreenManager *screenManager) {
    this->screenManager = screenManager;
}