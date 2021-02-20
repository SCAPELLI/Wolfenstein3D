#include "Server.h"
#include "../common/ProtectedEventsQueue.h"
#include "GameStage.h"
#include "Game.h"
#include "../common/Event.h"
#include "GameStage.h"
#include <unistd.h>
#include <iostream>

Server::Server(ProtectedEventsQueue& userEvents, ProtectedEventsQueue& updateEvents,
       std::atomic<bool>& quit):
        userEvents(userEvents), updateEvents(updateEvents), quit(quit) {}

void Server::operator()() {
    //std::vector<Event> updateEvents
    GameStage gameStage(updateEvents);
    while (!quit) {
        while (!userEvents.empty() && !quit) {
            Event event = std::move(userEvents.pop());
            event.runHandler(gameStage);
            //bot.generateEvents(userEvents, "map.yaml" o firstEvent.route);
            if (event.thisIsTheQuitEvent()) quit = true;
        }
        gameStage.incrementCooldown();
        usleep(2000);
    }
}
