
#include "DespawnEvent.h"

DespawnEvent::DespawnEvent (updateEventType eventType, int id, int type) : id(id), type(type), eventType(eventType) {}

void DespawnEvent::runHandler(GameStage &gameStage) {}

updateEventType DespawnEvent::getEventType() {
    return eventType;
}