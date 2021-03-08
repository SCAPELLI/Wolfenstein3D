#include "KillEvent.h"
#include "client/include/CGame.h"
#include "common/include/Event.h"
#include "common/include/EventSerializer.h"

KillEvent::KillEvent (updateEventType eventType, int idPlayer)
    : eventType(eventType), idPlayer(idPlayer){}



void KillEvent::runHandler(CGame& game) {
    game.processEvent(*this);
};
updateEventType KillEvent::getEventType() {
    return eventType;
}

std::string KillEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}