#include <SDL2/SDL.h>
#include "SDLContext.h"
#include "Window.h"
#include "EventsCatcher.h"
#include "GameStage.h"
#include "ProtectedEventQueue.h"

/*
class Server {
    ProtectedEventQueue& events;
public:
    explicit Server(ProtectedEventQueue& events): events(events) {}
    void operator()() {

    }
};*/

int main() {
    try {
        SDLContext context;
        Window window;
        EventsCatcher eventsCatcher;

        GameStage gameStage;
        ProtectedEventQueue events;
        bool quit = false;
        //lanzar hilo server
        //std::thread t {Server(protectedEventQueue, quit)}

        while (!quit) {
            events.insertEvents(eventsCatcher);

            // Serializar y enviar al server

            // lado server
            while (!events.empty()) {

                Event event = std::move(events.pop());
                event.runHandler(gameStage);
                if (event.thisIsTheQuitEvent()) quit = true;
            }
            // serializar y enviar al client

            // volver al lado client
            // recibir la actualizacion y renderizar

            SDL_Delay(200);
        }
        // joinear hilo server
    } catch (std::exception& exception) {
        exception.what();
    }
    return 0;
}
