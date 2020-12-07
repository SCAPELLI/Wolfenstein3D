#include "Server.h"
#include "ProtectedEventsQueue.h"
#include "GameStage.h"
#include "Event.h"
#include <unistd.h>

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
