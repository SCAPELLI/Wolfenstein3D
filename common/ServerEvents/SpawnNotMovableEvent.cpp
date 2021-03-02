

#include "SpawnNotMovableEvent.h"
#include "server/include/GameStage.h"
#include "client/include/CGame.h"
#include "common/include/EventSerializer.h"

void SpawnNotMovableEvent::runHandler(CGame& game) {
    game.processEvent (*this);
}

SpawnNotMovableEvent::SpawnNotMovableEvent(updateEventType eventType, int type,
                                           int posX, int posY)
        : type(type), posX(posX), posY(posY), eventType(eventType){}

updateEventType SpawnNotMovableEvent::getEventType() {
    return eventType;
}

std::string SpawnNotMovableEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}