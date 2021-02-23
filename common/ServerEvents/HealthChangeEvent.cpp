

#include "HealthChangeEvent.h"
#include "client/CGame.h"
HealthChangeEvent::HealthChangeEvent (updateEventType eventType,int idPLayer, int health)
:  eventType(eventType), idPlayer(idPLayer), health(health){}

updateEventType HealthChangeEvent::getEventType() {
    return eventType;
}
void HealthChangeEvent::runHandler(CGame &game) {
    game.processEvent(*this);
}