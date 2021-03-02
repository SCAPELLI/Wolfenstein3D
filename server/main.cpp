#include <SDL2/SDL.h>
#include <atomic>
#include "common/include/EventsCatcher.h"
#include "server/include/GameStage.h"
#include "common/include/ProtectedEventsQueue.h"
#include "common/include/BlockingEventsQueue.h"
#include "server/include/Server.h"
#include "server/include/GameLoader.h"
#include <thread>
#include <ServerEvents/CreateMapEvent.h>
#include "client/include/CGame.h"
#include "server/include/Map.h"

#define FOV 0.66

int main() {
    try {
        EventsCatcher eventsCatcher(1); // esta en client
        //-----------------
        ProtectedEventsQueue userEvents;

        std::vector<BlockingEventsQueue*> updateEvents;
        BlockingEventsQueue blockingQueue;
        updateEvents.push_back(&blockingQueue);
        std::atomic<bool> quit(false);
        std::thread t (Server(&userEvents, updateEvents, quit));

        bool hasStarted = false;
        while (!hasStarted){
            if (!updateEvents[0]->empty()){
                hasStarted = true;
            }
        }
        Event event = std::move(updateEvents[0]->pop());
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

            while (!updateEvents[0]->empty()) {
                Event event = std::move(updateEvents[0]->pop());
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
