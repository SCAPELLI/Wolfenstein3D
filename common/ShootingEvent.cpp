#include "ShootingEvent.h"
#include "client/CGame.h"
#include "../server/GameStage.h"
#include "EventSerializer.h"


//ShootingEvent::ShootingEvent(ShootingEvent& shootingEvent){}

ShootingEvent::ShootingEvent(int idPlayer) : idPlayer(idPlayer){}

void ShootingEvent::runHandler(CGame& renderer) {
    renderer.processEvent(*this);
}

void ShootingEvent::runHandler(GameStage &game) {
    game.processEvent(*this);
}

std::string ShootingEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}
