#include "ShootingEvent.h"
#include "Renderer.h"


ShootingEvent::ShootingEvent(ShootingEvent& shootingEvent){}

ShootingEvent::ShootingEvent(int idPlayer) : idPlayer(idPlayer){}

void ShootingEvent::runHandler(Renderer& renderer) {
    renderer.processEvent(*this);
};
