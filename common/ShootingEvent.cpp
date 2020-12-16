#include "ShootingEvent.h"
#include "Renderer.h"
#include "../cliente/CGame.h"


ShootingEvent::ShootingEvent(ShootingEvent& shootingEvent){}

ShootingEvent::ShootingEvent(int idPlayer) : idPlayer(idPlayer){}

void ShootingEvent::runHandler(CGame& renderer) {
    renderer.processEvent(*this);
};
