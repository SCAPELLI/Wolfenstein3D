

#include "HealthChangeEvent.h"
#include "../cliente/CGame.h"
HealthChangeEvent::HealthChangeEvent (updateEventType eventType, int health, int idPlayer)
: health(health), eventType(eventType), idPlayer(idPlayer){}

updateEventType HealthChangeEvent::getEventType() {
    return eventType;
}
void HealthChangeEvent::runHandler(CGame &game) {
    game.processEvent(*this);
}