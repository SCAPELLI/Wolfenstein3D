

#include "HealthChangeEvent.h"

HealthChangeEvent::HealthChangeEvent (updateEventType eventType, int health)
: health(health), eventType(eventType){}

updateEventType HealthChangeEvent::getEventType() {
    return eventType;
}