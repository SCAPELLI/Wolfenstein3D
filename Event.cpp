#include "Event.h"
#include "QuitEvent.h"
#include "MovementEvent.h"
#include "TurnEvent.h"

/*----------*/
#include "LifeDecrementEvent.h"
#include "GameOverEvent.h"
#include "ShootingEvent.h"
#include "PositionEvent.h"
/*----------*/

Event::Event(UpdateEventTypes eventType) {
    switch (eventType) {
        case LifeDecrement:
            event = new LifeDecrementEvent;
            break;
        case Shooting:
            event = new ShootingEvent;
            break;
        case Position:
            event = new PositionEvent;
        case GameOver:
            event = new GameOverEvent;
        default:
            event = nullptr;
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
            return new TurnEvent(ANTICLOCKWISE, 0.785);
        case SDLK_RIGHT:
            return new TurnEvent(CLOCKWISE, 0.785);
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
void Event::runHandler(Renderer& renderer) {
    if (event != nullptr) event->runHandler(renderer);
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
