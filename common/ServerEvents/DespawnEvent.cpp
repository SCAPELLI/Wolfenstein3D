
#include "DespawnEvent.h"
#include "../EventSerializer.h"
DespawnEvent::DespawnEvent (updateEventType eventType, int id, int type) : id(id), type(type), eventType(eventType) {}

void DespawnEvent::runHandler(GameStage &gameStage) {}

void DespawnEvent::runHandler(CGame& renderer){
    renderer.processEvent(*this);
}

updateEventType DespawnEvent::getEventType() {
    return eventType;
}
std::string DespawnEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}