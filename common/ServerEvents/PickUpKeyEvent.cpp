

#include "PickUpKeyEvent.h"

PickUpKeyEvent::PickUpKeyEvent (updateEventType eventType, int idPlayer)
: eventType(eventType), idPlayer(idPlayer) {}

updateEventType PickUpKeyEvent::getEventType() {
    return eventType;
}