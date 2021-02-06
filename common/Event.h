#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL_events.h>
#include "AbstractEvent.h"

class ProtectedEventsQueue;

enum updateEventType {KillEventType, ShootingEventType,
                        PositionEventType, GameOverEventType,
                        TurnEventType, OpenDoorType, SpawnEventType};

class Event {
    AbstractEvent* event;
public:
    explicit Event(AbstractEvent* updateEvent, updateEventType eventType);
    explicit Event(SDL_Event& sdlEvent);
    Event(Event&& originalEvent) noexcept;

    AbstractEvent* keyCodeLookUp(SDL_Event& sdlEvent);

    Event(const Event& anotherEvent) = delete;
    Event& operator = (const Event& anotherEvent) = delete;

    void runHandler(GameStage& gameStage);
    void runHandler(CGame& renderer);

    bool thisIsTheQuitEvent();
    bool thisIsAValidEvent();
    ~Event();
};

#endif
