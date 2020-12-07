#include <SDL_events.h>
#include "EventsCatcher.h"

std::queue<Event> EventsCatcher::getEvents() {
    std::queue<Event> eventQueue;
    SDL_Event sdlEvent;
    while( SDL_PollEvent( &sdlEvent ) != 0 ) {
            eventQueue.emplace(sdlEvent);
    }
    return eventQueue;
}
