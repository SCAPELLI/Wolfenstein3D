#include <iostream>
#include <common/EventSerializer.h>
#include "client/include/Client.h"
#include "client/include/TCPClient.h"
#include "client/include/CommunicationChannelClient.h"
#include "../../common/BlockingEventsQueue.h"
#include "../../common/ProtectedEventsQueue.h"
#include "../../common/ServerEvents/CreateMapEvent.h"
#include "../../server/include/ReceiverThread.h"
#include "../../server/include/SenderThread.h"
#include "../../common/include/Message.h"

#define FOV 0.66

Client::Client() {
    channel = new CommunicationChannelClient(userSocket);
    userId = -1;
    matchId = -1;
    maximumNumberOfPlayers = -1;
    levelId = -1;
}
Client::~Client() {
    delete channel;
}

bool Client::tryToConnect(std::string port, std::string domain) {
    try {
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
    int response = channel->receiveResponseOfJoiningAMatch();
    if (response == -1) {
        return false;
    } else {
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
        playMatch();
        return true;
    } else {
        return false;
    }
}
void Client::playMatch() {
    //EventsCatcher eventsCatcher(userId);
    BlockingEventsQueue senderQueue;
    ProtectedEventsQueue receiverQueue;

    ReceiverThread r(&userSocket, receiverQueue);
    r.start();

    bool hasStarted = false;
    while (!hasStarted){
        if (!receiverQueue.empty()){
            hasStarted = true;
        }
    }
    //Event event = std::move(receiverQueue.pop());

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

    CGame game(spawnPointX, spawnPointY, FOV, map, userId);
    for (auto it = start->startingLocations.begin(); it != start->startingLocations.end(); ++it){
        if (it->first == userId) continue;
        game.spawnEnemy(it->first, Vector(start->startingLocations[it->first].first,
                                          start->startingLocations[it->first].second));
    }

    SenderThread s(&userSocket, &senderQueue);
    s.start();
    bool quit = false;
    while (!quit) {

        while (!receiverQueue.empty()) {
            Event event = std::move(receiverQueue.pop());
            event.runHandler(game);
        }
        game.draw();
        game.playSounds();
        game.advanceTime();
        quit = game.isOver;
        senderQueue.insertEvents(eventsCatcher);
        SDL_Delay(33);
    }
}