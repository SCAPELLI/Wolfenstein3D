#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL_events.h>
#include "AbstractEvent.h"
#include "Constants.h"
class ProtectedEventsQueue;


class Event {
public:
    AbstractEvent* event;
    explicit Event(AbstractEvent* updateEvent, eventType eventType);
    explicit Event(SDL_Event& sdlEvent);
    Event(Event&& originalEvent) noexcept;
    Event();
    Event& operator= (Event&& anotherEvent) noexcept;

    AbstractEvent* keyCodeLookUp(SDL_Event& sdlEvent);

    Event(const Event& anotherEvent) = delete;
    Event& operator = (const Event& anotherEvent) = delete;

    void runHandler(GameStage& gameStage);
    void runHandler(CGame& renderer);

    std::string getSerialization();

    bool thisIsTheQuitEvent();
    bool thisIsAValidEvent();
    ~Event();
};

#endif
