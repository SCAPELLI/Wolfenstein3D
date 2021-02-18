

#include "DoorOpenedEvent.h"
#include "../EventSerializer.h"
#include "../../cliente/CGame.h"

DoorOpenedEvent::DoorOpenedEvent (updateEventType eventType, int uniqueId)
: uniqueId(uniqueId), eventType(eventType) {}

updateEventType DoorOpenedEvent::getEventType() {
    return eventType;
}

//std::string DoorOpenedEvent::getSerialization() {
//    return EventSerializer::serialize(*this);
//}
void DoorOpenedEvent::runHandler(CGame& game) {
    game.processEvent(*this);
};