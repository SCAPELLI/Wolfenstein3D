#include "Event.h"
#include "QuitEvent.h"
#include "KeyUpEvent.h"
#include "KeyDownEvent.h"
#include "KeyLeftEvent.h"
#include "KeyRightEvent.h"

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
            return new KeyUpEvent;
        case SDLK_DOWN:
            return new KeyDownEvent;
        case SDLK_LEFT:
            return new KeyLeftEvent;
        case SDLK_RIGHT:
            return new KeyRightEvent;
        default:
            return nullptr;
    }
}
void Event::runHandler() {
    if (event != nullptr) event->runHandler();
}
bool Event::thisIsTheQuitEvent() {
    if (event != nullptr) return event->thisIsTheQuitEvent();
    return false;
}
Event::~Event() {
    delete event;
}
