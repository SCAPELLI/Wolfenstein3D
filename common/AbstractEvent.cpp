#include "AbstractEvent.h"

bool AbstractEvent::thisIsTheQuitEvent() {
    return false;
}

updateEventType AbstractEvent::getEventType() {
    return eventType;
}