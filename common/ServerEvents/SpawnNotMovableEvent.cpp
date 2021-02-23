

#include "SpawnNotMovableEvent.h"
#include "server/GameStage.h"
#include "client/CGame.h"

void SpawnNotMovableEvent::runHandler(CGame& game) {
    game.processEvent (*this);
}

SpawnNotMovableEvent::SpawnNotMovableEvent(updateEventType eventType, int type,
                                           int posX, int posY)
        : type(type), posX(posX), posY(posY), eventType(eventType){}

updateEventType SpawnNotMovableEvent::getEventType() {
    return eventType;
}