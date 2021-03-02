
#include "../include/Match.h"
#include "../../common/include/Socket.h"
#include "server/include/GameStage.h"
#include "../../server/include/CommunicationChannelServer.h"
#include "common/include/ProtectedEventsQueue.h"
#include "common/include/BlockingEventsQueue.h"
#include "../include/ReceiverThread.h"
#include "../include/SenderThread.h"
#include "../ai/AI.h"
#include <unistd.h>
#include <cctype>
#include <common/include/EventSerializer.h>
#include <algorithm>
#include "../../common/include/Message.h"
#include "../../server/include/ProtectedLobby.h"


Match::Match(int matchId, int levelId, int maximumNumberOfPlayers,
             int adminUserId, str adminUserName, Socket* adminUserSocket, ProtectedLobby* lobby, char* configPath):
             matchId(matchId),levelId(levelId),
             maximumNumberOfPlayers(maximumNumberOfPlayers),
             adminUserId(adminUserId),
             matchStarted(false),
             matchFinished(false),
             matchCancelled(false),
             lobby(lobby), 
             configPath(configPath) {
    addUser(adminUserName, adminUserId, adminUserSocket);
    }
void Match::addUser(str userName, int userId, Socket* userSocket) {
    users[userName] = userId;
    usersSockets[userId] = userSocket;
}

int Match::getActualNumberOfUsers() const {
    return users.size();
}
bool Match::sameIdAs(int aMatchId) const {
    return matchId == aMatchId;
}
bool Match::isNotFull() const {
    return maximumNumberOfPlayers > users.size();
}
bool Match::userIsPartOfTheMatch (str userName, int userId) const {
    auto it = users.find(userName);
    if (it != users.end())
        return it->second == userId;
    else
        return false;
}
bool Match::userIsAdmin(int userId) const {
    return userId == adminUserId;
}
void Match::removeUser(str userName, int userId) {
    if (userIsPartOfTheMatch(userName, userId))
        users.erase(userName);
    if (usersSockets.find(userId) != usersSockets.end())
        usersSockets.erase(userId);
}
bool Match::notStarted() const {
    return !matchStarted;
}
void Match::cancelMatch() {
    matchCancelled = true;
}
MatchInfo Match::getMatchInfo() const {
    return {matchId, levelId, maximumNumberOfPlayers, (int)users.size()};
}

void Match::removeUser(Event* event) {
    int playerId = ((QuitEvent*)event->event)->playerId;

    auto it = std::find_if(users.begin(),users.end(),
                           [&](const std::pair<str, int>& user) {return user.second == playerId; });
    if (it != users.end())
        users.erase(it);
}

bool Match::userIsPartOfTheMatch(int userId) {
    auto it = std::find_if(users.begin(),users.end(),
                           [&](const std::pair<str, int>& user) {return user.second == userId; });
    return it != users.end();
}

bool senderThreadIsDead(SenderThread* t){
    //if (t->isDead()){
        t->join();
        delete t;
        std::cout<<"uni el hilo enviador"<<std::endl;
        return true;
    //}
    //return t->isDead();
}

bool receiverThreadIsDead(ReceiverThread* t){
    //if (t->isDead()){
        t->join();
        delete t;
        std::cout<<"uni el hilo recibidor"<<std::endl;
        return true;
    //}
    return t->isDead();
}

void Match::run() {

    for (auto& user: users)
        CommunicationChannelServer::sendMatchStartedSignal(usersSockets[user.second]);
    matchStarted = true;

    ProtectedEventsQueue userEvents;
    std::vector<BlockingEventsQueue> updateEvents(users.size()); // equivalente a updateEvents x N

    std::map<int, std::string> players;
    players[0] = "ai";
    for (auto it = users.begin(); it != users.end(); ++it) {
        players[it->second] = it->first;
    }
    GameStage gameStage(&updateEvents, players, levelId, configPath); // agregar levelId a GameStage


    std::vector<ReceiverThread*> receivers; // punteros?
    std::vector<SenderThread*> senders;
    int i = 0;
    for (auto it = usersSockets.begin(); it != usersSockets.end(); ++it){
        receivers.push_back(new ReceiverThread(it->second, &userEvents, it->first)); //OJO CON ESTOS NEW, NO TIENEN DELETE
        senders.push_back(new SenderThread(it->second, &updateEvents[i], it->first));
        receivers[i]->start();
        senders[i]->start();
        i++;
    }

    std::cout<< "se ejecutó una partida con "<<users.size()<<" jugadores"<<std::endl;
    // agregar joins
    AI ai(levelId);
    std::list<Message> messageEvents;
    while (!matchFinished){
        messageEvents = std::move(userEvents.popAll());
        while (!messageEvents.empty()) {
            Event event = std::move(EventSerializer::deserialize(messageEvents.front().getMessage()));
            messageEvents.pop_front();
            event.runHandler(gameStage); //agrege un while mas para procesar la lista de eventos
            if (event.thisIsTheQuitEvent()) {
                removeUser(&event);
                if (gameStage.gameFinished() or users.empty())
                    matchFinished = true;
                lobby->notifyAll();
            }
        }

        ai.generateEvent(userEvents, gameStage.getPlayersInfo());
        gameStage.incrementCooldown();
        usleep(20000);
        gameStage.ifSomeoneWinNotifyHim();
    }
    senders.erase(std::remove_if(senders.begin(), senders.end(), senderThreadIsDead), senders.end());
    receivers.erase(std::remove_if(receivers.begin(), receivers.end(), receiverThreadIsDead), receivers.end());

    matchFinished = true;
    std::cout<<"llego a salir de la partida"<<std::endl;
    lobby->notifyAll();
}

bool Match::notFinished() const {
    return !matchFinished;
}
bool Match::notCancelled() const {
    return !matchCancelled;
}
