#include "common/include/ShootingEvent.h"
#include "client/include/CGame.h"
#include "server/include/GameStage.h"
#include "common/include/EventSerializer.h"


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
