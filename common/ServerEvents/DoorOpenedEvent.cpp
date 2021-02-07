

#include "DoorOpenedEvent.h"

DoorOpenedEvent::DoorOpenedEvent (updateEventType eventType, int uniqueId)
: uniqueId(uniqueId), eventType(eventType) {}

updateEventType DoorOpenedEvent::getEventType() {
    return eventType;
}