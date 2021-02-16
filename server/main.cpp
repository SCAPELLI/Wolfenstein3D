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
#include "../cliente/CGame.h"
#include "Map.h"

int main() {
    try {
        EventsCatcher eventsCatcher;

        //-----------------
        ProtectedEventsQueue userEvents;
        ProtectedEventsQueue updateEvents;
        std::atomic<bool> quit(false);
        //-----------------
        CGame game(32, 64,0.66);
        //-----------------
        std::thread t (Server(userEvents, updateEvents, quit));
        Map map = Map();
        while (!quit) {
            userEvents.insertEvents(eventsCatcher);
            // Serializar eventos de usuario y enviar al server.
            // Recibir Eventos de server serializados.

            // Se carga el updateEvents

            // Renderizar actualizaciones

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
