#include <SDL2/SDL.h>
#include <atomic>
//#include "../common/SDLContext.h"
//#include "../common/Window.h"
#include "../common/EventsCatcher.h"
#include "GameStage.h"
#include "../common/ProtectedEventsQueue.h"
#include "Server.h"
#include "GameLoader.h"
#include <thread>
#include <ServerEvents/CreateMapEvent.h>
#include "../cliente/CGame.h"
#include "Map.h"

#define FOV 0.66

int main() {
    try {
        EventsCatcher eventsCatcher;

        //-----------------
        ProtectedEventsQueue userEvents;
        ProtectedEventsQueue updateEvents;
        std::atomic<bool> quit(false);
        std::thread t (Server(userEvents, updateEvents, quit));

        bool hasStarted = false;
        while (!hasStarted){
            if (!updateEvents.empty()){
                hasStarted = true;
            }
        }
        Event event = std::move(updateEvents.pop());
        CreateMapEvent* start = (CreateMapEvent*) event.event;
        Vector spawnPoint = start->startingLocations[0];

        // Create map
        std::vector<std::vector<int>> map;
        for (int i = 0; i <= start->width; i++){
            std::vector<int> row;
            for (int j = 0; j <= start->height; j++){
                row.push_back(0);
            }
            map.push_back(row);
        }

        CGame game(spawnPoint.x, spawnPoint.y, FOV, map);
        while (!quit) {
            userEvents.insertEvents(eventsCatcher);

            while (!updateEvents.empty()) {
                Event event = std::move(updateEvents.pop());
                event.runHandler(game);
            }
            game.draw();
            game.playSounds();
            game.advanceTime();
            SDL_Delay(33);
        }

        t.join();
    } catch (std::exception& exception) {
        exception.what();
    }
    return 0;
}
