#include "Event.h"
#include "QuitEvent.h"
#include "MovementEvent.h"
#include "TurnEvent.h"

/*----------*/
#include "LifeDecrementEvent.h"
#include "GameOverEvent.h"
#include "ShootingEvent.h"
#include "PositionEvent.h"
#include "OpenDoorEvent.h"
/*----------*/

#define PI 3.141592

Event::Event(AbstractEvent* updateEvent, updateEventType eventType) {
    switch (eventType) {
        case LifeDecrementEventType:
            event = new LifeDecrementEvent(*(LifeDecrementEvent*)updateEvent);
            break;
        case ShootingEventType:
            event = new ShootingEvent(*(ShootingEvent*)updateEvent);
            break;
        case PositionEventType:
            event = new PositionEvent(*(PositionEvent*)updateEvent);
            break;
        case GameOverEventType:
            event = new GameOverEvent(*(GameOverEvent*)updateEvent);
            break;
        case TurnEventType:
            event = new TurnEvent(*(TurnEvent*)updateEvent);
            break;
            case OpenDoorType:
            event = new OpenDoorEvent(*(OpenDoorEvent*)updateEvent);
            break;
        default:
            this->event = nullptr;
    }
}

Event::Event(SDL_Event& sdlEvent) {
    switch (sdlEvent.type) {
        case SDL_QUIT:
            event = new QuitEvent;
            break;
        case SDL_KEYDOWN:
            event = keyCodeLookUp(sdlEvent);
            break;
        default:
            event = nullptr;
    }
}

AbstractEvent* Event::keyCodeLookUp(SDL_Event& sdlEvent) {
    switch (sdlEvent.key.keysym.sym) {
        case SDLK_UP:
            return new MovementEvent(FOWARD, 0);
        case SDLK_DOWN:
            return new MovementEvent(BACKWARD, 0);
        case SDLK_LEFT:
            return new TurnEvent(0, PI/180);
        case SDLK_RIGHT:
            return new TurnEvent(0, -PI/180);
        default:
            return nullptr;
    }
}
Event::Event(Event&& originalEvent) noexcept {
    event = originalEvent.event;
    originalEvent.event = nullptr;
}
void Event::runHandler(GameStage& gameStage) {
    if (event != nullptr) event->runHandler(gameStage);
}
/*-----------*/
void Event::runHandler(CGame& game) {
    if (event != nullptr) event->runHandler(game);
}
/*-----------*/
bool Event::thisIsTheQuitEvent() {
    if (event != nullptr) return event->thisIsTheQuitEvent();
    return false;
}
bool Event::thisIsAValidEvent() {
    return event != nullptr;
}
Event::~Event() {
    delete event;
}
