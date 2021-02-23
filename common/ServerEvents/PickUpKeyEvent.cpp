

#include "PickUpKeyEvent.h"
#include "../EventSerializer.h"

PickUpKeyEvent::PickUpKeyEvent (updateEventType eventType, int idPlayer)
: eventType(eventType), idPlayer(idPlayer) {}

updateEventType PickUpKeyEvent::getEventType() {
    return eventType;
}

std::string PickUpKeyEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}