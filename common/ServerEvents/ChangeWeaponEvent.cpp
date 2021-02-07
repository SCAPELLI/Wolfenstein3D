

#include "ChangeWeaponEvent.h"
#include "Event.h"


ChangeWeaponEvent::ChangeWeaponEvent (updateEventType eventType, int idPlayer, int uniqueId)
: idPlayer(idPlayer), uniqueId(uniqueId), eventType(eventType){}

updateEventType ChangeWeaponEvent::getEventType() {
    return eventType;
}