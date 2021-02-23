#include "AmmoChangeEvent.h"
#include "client/CGame.h"

AmmoChangeEvent::AmmoChangeEvent (updateEventType eventType, int ammo)
: eventType(eventType), ammo(ammo){}

void AmmoChangeEvent::runHandler(CGame &game) {
    game.processEvent(*this);
}

updateEventType AmmoChangeEvent::getEventType() {
    return eventType;
}