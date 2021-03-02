#include <SDL2/SDL_events.h>
#include "common/include/EventsCatcher.h"
#include "common/include/EventSerializer.h"
EventsCatcher::EventsCatcher(int playerId): playerId(playerId){}

std::queue<Message> EventsCatcher::getEvents() {
    std::queue<Message> messageQueue;
    SDL_Event sdlEvent;
    while( SDL_PollEvent( &sdlEvent ) != 0 ) {
            Event event(sdlEvent, playerId);
            if (event.thisIsAValidEvent())
                messageQueue.push(EventSerializer::serialize(event));
    }
    return messageQueue;
}
