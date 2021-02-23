
#include "../include/Match.h"
#include "../../common/include/Socket.h"
#include "../GameStage.h"
#include "../../server/include/CommunicationChannelServer.h"
#include "../../common/ProtectedEventsQueue.h"
#include "../../common/BlockingEventsQueue.h"
#include "../include/ReceiverThread.h"
#include "../include/SenderThread.h"
#include "../ai/AI.h"
#include <unistd.h>



Match::Match(int matchId, int levelId, int maximumNumberOfPlayers,
             int adminUserId, str adminUserName, Socket* adminUserSocket):
             matchId(matchId),levelId(levelId),
             maximumNumberOfPlayers(maximumNumberOfPlayers),
             adminUserId(adminUserId),
             matchStarted(false),
             matchFinished(false),
             matchCancelled(false) {
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

void Match::run() {

    for (auto& user: users)
        CommunicationChannelServer::sendMatchStartedSignal(usersSockets[user.second]);
    matchStarted = true;

    ProtectedEventsQueue userEvents;
    std::vector<BlockingEventsQueue> updateEvents(users.size()); // equivalente a updateEvents x N

    std::map<int, std::string> players;
    for (auto it = users.begin(); it != users.end(); ++it)
        players[it->second] = it->first;


    std::vector<ReceiverThread*> receivers; // punteros?
    std::vector<SenderThread*> senders;
    int i = 0;
    for (auto it = usersSockets.begin(); it != usersSockets.end(); ++it){
        receivers.push_back(new ReceiverThread(it->second, userEvents)); // emplace_back o new?
        senders.push_back(new SenderThread(it->second, &updateEvents[i]));
        receivers[i]->start();
        senders[i]->start();
        i++;
    }

    GameStage gameStage(updateEvents, players, levelId); // agregar levelId a GameStage
    std::cout<< "se ejecutó una partida con "<<users.size()<<" jugadores"<<std::endl;
    // agregar joins
    //AI ai(levelId);
    while (!matchFinished){
        while(!userEvents.empty() && !matchFinished){ //procesar eventos
            Event event = std::move(userEvents.pop());
            event.runHandler(gameStage);
        } // agregar reap?
       // ai.generateEvent(userEvents, gameStage.getPlayersInfo());
        gameStage.incrementCooldown();
        usleep(20000);
    }
    matchFinished = true;
}

bool Match::notFinished() const {
    return !matchFinished;
}
bool Match::notCancelled() const {
    return !matchCancelled;
}
