#include "StartEvent.h"
#include "common/include/EventSerializer.h"
#include "client/include/CGame.h"

StartEvent::StartEvent(updateEventType eventType): eventType(eventType){}

std::string StartEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}

updateEventType StartEvent::getEventType() {
    return eventType;
}

bool StartEvent::thisIsTheStartEvent() {
    return true;
}