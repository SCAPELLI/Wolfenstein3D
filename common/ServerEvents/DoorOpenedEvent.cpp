

#include "DoorOpenedEvent.h"
#include "common/include/EventSerializer.h"
#include "client/include/CGame.h"

DoorOpenedEvent::DoorOpenedEvent (updateEventType eventType, int x, int y)
: x(x), y(y), eventType(eventType) {}

updateEventType DoorOpenedEvent::getEventType() {
    return eventType;
}

std::string DoorOpenedEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}
void DoorOpenedEvent::runHandler(CGame& game) {
    game.processEvent(*this);
};