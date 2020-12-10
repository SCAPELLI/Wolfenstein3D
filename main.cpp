#include <SDL2/SDL.h>
#include <atomic>
#include "SDLContext.h"
#include "Window.h"
#include "EventsCatcher.h"
#include "GameStage.h"
#include "ProtectedEventsQueue.h"
#include "Server.h"
#include "GameLoader.h"
#include <thread>

#include "Renderer.h"

int main() {
    try {
        SDLContext context;
        Window window;
        EventsCatcher eventsCatcher;

        /*-----------------*/
        ProtectedEventsQueue userEvents;
        ProtectedEventsQueue updateEvents;
        std::atomic<bool> quit(false);
        /*-----------------*/
        Renderer renderer;
        /*-----------------*/
        //GameLoader yaml;
        // Game game  = yaml.readData();
        std::thread t (Server(userEvents, updateEvents, quit));

        while (!quit) {
            userEvents.insertEvents(eventsCatcher);

            // Serializar eventos de usuario y enviar al server.
            // Recibir Eventos de server serializados.

            // Se carga el updateEvents

            // Renderizar actualizaciones

            while (!updateEvents.empty()) {
                Event event = std::move(updateEvents.pop());
                event.runHandler(renderer);
            }

            SDL_Delay(200);
        }

        t.join();
    } catch (std::exception& exception) {
        exception.what();
    }
    return 0;
}
