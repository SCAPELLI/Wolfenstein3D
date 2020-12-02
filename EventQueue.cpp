#include <SDL_events.h>
#include "EventQueue.h"

std::queue<Event> EventQueue::getEvents() {
    std::queue<Event> eventQueue;
    SDL_Event sdlEvent;
    while( SDL_PollEvent( &sdlEvent ) != 0 ) {
        eventQueue.emplace(sdlEvent);
    }
    return eventQueue;
}
