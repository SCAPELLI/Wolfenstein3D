#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL_events.h>
#include "AbstractEvent.h"
#include "Constants.h"

/*Eventos del juego*/
class Event {
public:
    AbstractEvent* event;
    Event(AbstractEvent* updateEvent, updateEventType eventType);
    Event(SDL_Event& sdlEvent, int playerId);
    Event(Event&& originalEvent) noexcept;
    Event();
    Event& operator= (Event&& anotherEvent) noexcept;

    AbstractEvent* keyCodeLookUp(SDL_Event& sdlEvent, int playerId);

    Event(const Event& anotherEvent) = delete;
    Event& operator = (const Event& anotherEvent) = delete;

    void runHandler(GameStage& gameStage);
    void runHandler(CGame& renderer);

    std::string getSerialization();

    bool thisIsTheQuitEvent();
    bool thisIsTheStartEvent();
    bool thisIsAValidEvent();
    ~Event();
};

#endif
