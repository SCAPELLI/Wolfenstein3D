#include "Server.h"
#include "../common/ProtectedEventsQueue.h"
#include "GameStage.h"
#include "Game.h"
#include "../common/Event.h"
#include "GameStage.h"
#include <unistd.h>
#include <iostream>
#include "../ai/AI.h"

Server::Server(std::vector<BlockingEventsQueue>& usersEvents,
                                std::vector<BlockingEventsQueue>& updateEvents,
                                std::atomic<bool>& quit):
        userEvents(userEvents), updateEvents(updateEvents), quit(quit) {}

void Server::operator()() {
    std::map<int, std::string> players;
    players[0] = "bot";
    players[1] = "killn";
    int levelId = 1; //sacar cuando se haga el match::run()
    GameStage gameStage(updateEvents, players, levelId);
    AI ai(levelId);
    while (!quit) {
        while (!userEvents.empty() && !quit) {
            Event event = std::move((userEvents.at(0)).pop());
            event.runHandler(gameStage);
            if (event.thisIsTheQuitEvent()) quit = true;
        }
        ai.generateEvent(userEvents[0], gameStage.getPlayersInfo());
        gameStage.incrementCooldown();
        usleep(20000);
    }
}
