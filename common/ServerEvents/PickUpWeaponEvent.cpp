

#include "PickUpWeaponEvent.h"


PickUpWeaponEvent::PickUpWeaponEvent (updateEventType eventType, int uniqueId)
: uniqueId(uniqueId), eventType(eventType) {}

updateEventType PickUpWeaponEvent::getEventType() {
    return eventType;
}