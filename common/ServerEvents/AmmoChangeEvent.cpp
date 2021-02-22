#include "AmmoChangeEvent.h"
#include "cliente/CGame.h"

AmmoChangeEvent::AmmoChangeEvent (updateEventType eventType, int idPlayer, int ammo)
: eventType(eventType),idPlayer(idPlayer), ammo(ammo) {}

void AmmoChangeEvent::runHandler(CGame &game) {
    game.processEvent(*this);
}

updateEventType AmmoChangeEvent::getEventType() {
    return eventType;
}