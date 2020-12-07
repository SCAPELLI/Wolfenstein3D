#include "Event.h"
#include "QuitEvent.h"
#include "MovementEvent.h"
#include "TurnEvent.h"

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
            return new MovementEvent(FOWARD);
        case SDLK_DOWN:
            return new MovementEvent(BACKWARD);
        case SDLK_LEFT:
            return new TurnEvent(ANTICLOCKWISE);;
        case SDLK_RIGHT:
            return new TurnEvent(CLOCKWISE);
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
bool Event::thisIsTheQuitEvent() {
    if (event != nullptr) return event->thisIsTheQuitEvent();
    return false;
}
Event::~Event() {
    delete event;
}
