#include "AmmoChangeEvent.h"


AmmoChangeEvent::AmmoChangeEvent (updateEventType eventType, int ammo)
: eventType(eventType), ammo(ammo){}

updateEventType AmmoChangeEvent::getEventType() {
    return eventType;
}