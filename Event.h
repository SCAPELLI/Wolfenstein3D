#ifndef EVENT_H
#define EVENT_H

#include <SDL_events.h>
#include "AbstractEvent.h"

class Event {
    AbstractEvent* event;
public:
    explicit Event(SDL_Event& sdlEvent);
    Event(Event&& originalEvent) noexcept;

    AbstractEvent* keyCodeLookUp(SDL_Event& sdlEvent);

    Event(const Event& anotherEvent) = delete;
    Event& operator = (const Event& anotherEvent) = delete;

    void runHandler(GameStage& gameStage);
    bool thisIsTheQuitEvent();
    ~Event();
};

#endif
