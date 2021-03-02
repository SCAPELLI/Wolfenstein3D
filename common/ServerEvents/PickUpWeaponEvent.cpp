

#include "PickUpWeaponEvent.h"
#include "common/include/EventSerializer.h"

PickUpWeaponEvent::PickUpWeaponEvent (updateEventType eventType, int idPlayer, int uniqueId)
: eventType(eventType), idPlayer(idPlayer), uniqueId(uniqueId) {}

updateEventType PickUpWeaponEvent::getEventType() {
    return eventType;
}

std::string PickUpWeaponEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}