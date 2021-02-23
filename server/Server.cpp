#include "Server.h"
#include "../common/ProtectedEventsQueue.h"
#include "../common/BlockingEventsQueue.h"
#include "GameStage.h"
#include "Game.h"
#include "../common/ProtectedEventsQueue.h"
#include "GameStage.h"
#include <unistd.h>
#include <iostream>
#include "../ai/AI.h"

Server::Server(ProtectedEventsQueue* usersEvent,
                                std::vector<BlockingEventsQueue>& updateEvents,
                                std::atomic<bool>& quit):
        userEvents(usersEvent), updateEvents(updateEvents), quit(quit) {}

void Server::operator()() {
    std::map<int, std::string> players;
    players[0] = "bot";
    players[1] = "killn";
    int levelId = 1; //sacar cuando se haga el match::run()
    GameStage gameStage(updateEvents, players, levelId);
    AI ai(levelId);
    while (!quit) {
        while (!userEvents->empty() && !quit) {
            Event event = std::move((userEvents->pop()));
            event.runHandler(gameStage);
            if (event.thisIsTheQuitEvent()) quit = true;
        }
        //ai.generateEvent(userEvents, gameStage.getPlayersInfo());
        gameStage.incrementCooldown();
        usleep(20000);
    }
}
