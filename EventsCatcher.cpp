#include <SDL_events.h>
#include "EventsCatcher.h"

std::queue<Event> EventsCatcher::getEvents() {
    std::queue<Event> eventQueue;
    SDL_Event sdlEvent;
    while( SDL_PollEvent( &sdlEvent ) != 0 ) {
            Event event(sdlEvent);
            if (event.thisIsAValidEvent()) eventQueue.push(std::move(event));
    }
    return eventQueue;
}
