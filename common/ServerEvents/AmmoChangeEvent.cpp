#include "AmmoChangeEvent.h"
#include "cliente/CGame.h"

AmmoChangeEvent::AmmoChangeEvent (updateEventType eventType, int ammo, int idPlayer)
: eventType(eventType), ammo(ammo), idPlayer(idPlayer){}

void AmmoChangeEvent::runHandler(CGame &game) {
    game.processEvent(*this);
}

updateEventType AmmoChangeEvent::getEventType() {
    return eventType;
}