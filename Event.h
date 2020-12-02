#ifndef EVENT_H
#define EVENT_H

#include <SDL_events.h>
#include "AbstractEvent.h"

class Event {
    AbstractEvent* event;
public:
    explicit Event(SDL_Event& sdlEvent);

    AbstractEvent* keyCodeLookUp(SDL_Event& sdlEvent);

    void runHandler();
    bool thisIsTheQuitEvent();
    ~Event();
};

#endif
