#include "common/ServerEvents/KillEvent.h"
#include "client/CGame.h"
#include "common/Event.h"
#include "common/EventSerializer.h"

KillEvent::KillEvent (updateEventType eventType, int idPlayer) //kil
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