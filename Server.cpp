#include "Server.h"
#include "ProtectedEventsQueue.h"
#include "GameStage.h"
#include "Game.h"
#include "Event.h"
#include "GameLoader.h"
#include <unistd.h>
#include <iostream>

Server::Server(ProtectedEventsQueue& userEvents, ProtectedEventsQueue& updateEvents,
       std::atomic<bool>& quit):
        userEvents(userEvents), updateEvents(updateEvents), quit(quit) {}

void Server::operator()() {
    GameStage gameStage(updateEvents);
    while (!quit) {
        while (!userEvents.empty() && !quit) {
            Event event = std::move(userEvents.pop());
            event.runHandler(gameStage);
            if (event.thisIsTheQuitEvent()) quit = true;
        }
        usleep(2000);
    }
}
