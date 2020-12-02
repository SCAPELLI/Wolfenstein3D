#include <queue>
#include "SDLContext.h"
#include "Window.h"
#include "EventQueue.h"

int main() {
    try {
        SDLContext context;
        Window window;
        EventQueue eventQueue;

        bool quit = false;
        while (!quit) {
            std::queue<Event> events = std::move(eventQueue.getEvents());
            // Serializar y enviar al server

            // lado server
            while (!events.empty()) {
                events.front().runHandler();
                if (events.front().thisIsTheQuitEvent()) quit = true;
                events.pop();
            }
            // serializar y enviar al client

            // volver al lado client
            // recibir la actualizacion y renderizar
        }
    } catch (std::exception& exception) {
        exception.what();
    }
    return 0;
}
