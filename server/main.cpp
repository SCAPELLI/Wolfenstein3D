#include <SDL2/SDL.h>
#include <atomic>
#include "../common/EventsCatcher.h"
#include "GameStage.h"
#include "../common/ProtectedEventsQueue.h"
#include "../common/BlockingEventsQueue.h"
#include "Server.h"
#include "GameLoader.h"
#include <thread>
#include <ServerEvents/CreateMapEvent.h>
#include "../cliente/CGame.h"
#include "Map.h"

#define FOV 0.66

int main() {
    try {
        EventsCatcher eventsCatcher(1); // esta en client
        //-----------------
        ProtectedEventsQueue userEvents;
        std::vector<BlockingEventsQueue> updateEvents;
        std::atomic<bool> quit(false);
        std::thread t (Server(&userEvents, updateEvents, quit));

        bool hasStarted = false;
        while (!hasStarted){
            if (!updateEvents.empty()){
                hasStarted = true;
            }
        }
        Event event = std::move(updateEvents[0].pop());
        CreateMapEvent* start = (CreateMapEvent*) event.event;
        double spawnPointX = start->startingLocations[1].first;
        double spawnPointY = start->startingLocations[1].second;

        // Create empty map
        std::vector<std::vector<int>> map;
        for (int i = 0; i <= start->height; i++){
            std::vector<int> row;
            for (int j = 0; j <= start->width; j++){
                row.push_back(0);
            }
            map.push_back(row);
        }

        CGame game(spawnPointX, spawnPointY, FOV, map, 1);
        game.spawnEnemy(0, Vector(start->startingLocations[0].first, start->startingLocations[0].second));
        while (!quit) {
            userEvents.insertEvents(eventsCatcher);

            while (!userEvents.empty()) {
                Event event = std::move(userEvents.pop());
                event.runHandler(game);
            }
            game.draw();
            game.playSounds();
            game.advanceTime();
            quit = game.isOver;
            SDL_Delay(33);
        }

        t.join();
    } catch (std::exception& exception) {
        exception.what();
    }
    return 0;
}
