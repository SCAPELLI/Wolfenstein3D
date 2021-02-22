

#include "PickUpWeaponEvent.h"


PickUpWeaponEvent::PickUpWeaponEvent (updateEventType eventType, int idPlayer, int uniqueId)
: eventType(eventType), idPlayer(idPlayer), uniqueId(uniqueId) {}

updateEventType PickUpWeaponEvent::getEventType() {
    return eventType;
}