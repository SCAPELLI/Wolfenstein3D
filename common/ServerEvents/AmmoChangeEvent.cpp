#include "AmmoChangeEvent.h"
#include "client/include/CGame.h"
#include "common/include/EventSerializer.h"

AmmoChangeEvent::AmmoChangeEvent (updateEventType eventType, int idPlayer, int ammo)
: eventType(eventType),idPlayer(idPlayer), ammo(ammo) {}

void AmmoChangeEvent::runHandler(CGame &game) {
    game.processEvent(*this);
}

updateEventType AmmoChangeEvent::getEventType() {
    return eventType;
}
std::string AmmoChangeEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}