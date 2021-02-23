

#include "HealthChangeEvent.h"
#include "client/CGame.h"
HealthChangeEvent::HealthChangeEvent (updateEventType eventType, int health)
: health(health), eventType(eventType){}

updateEventType HealthChangeEvent::getEventType() {
    return eventType;
}
void HealthChangeEvent::runHandler(CGame &game) {
    game.processEvent(*this);
}