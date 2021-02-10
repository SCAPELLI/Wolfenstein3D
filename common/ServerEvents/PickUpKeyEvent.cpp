

#include "PickUpKeyEvent.h"

PickUpKeyEvent::PickUpKeyEvent (updateEventType eventType)
: eventType(eventType) {}

updateEventType PickUpKeyEvent::getEventType() {
    return eventType;
}