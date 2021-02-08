#include "ServerEvents/KillEvent.h"
#include "Renderer.h"
#include "cliente/CGame.h"
#include "Event.h"

KillEvent::KillEvent (updateEventType eventType, int idPlayer) //kill
    :idPlayer(idPlayer), eventType(eventType){}

KillEvent::KillEvent (KillEvent& KillEvent)
{}

void KillEvent::runHandler(CGame& game) {
    game.processEvent(*this);
};
updateEventType KillEvent::getEventType() {
    return eventType;
}