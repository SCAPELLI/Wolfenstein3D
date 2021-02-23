

#include "SpawnEvent.h"
#include "server/GameStage.h"

void SpawnEvent::runHandler(CGame& game) {
    game.processEvent (*this);
};

SpawnEvent::SpawnEvent (updateEventType eventType, int id, int type, int posX, int posY)
: id(id), type(type), posX(posX), posY(posY), eventType(eventType){}

updateEventType SpawnEvent::getEventType() {
    return eventType;
}