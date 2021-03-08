#include "common/include/AbstractEvent.h"

bool AbstractEvent::thisIsTheQuitEvent() {
    return false;
}

updateEventType AbstractEvent::getEventType() {
    return eventType;
}
std::string AbstractEvent::getSerialization() {
    return "";
}

bool AbstractEvent::thisIsTheStartEvent() {
    return false;
}
