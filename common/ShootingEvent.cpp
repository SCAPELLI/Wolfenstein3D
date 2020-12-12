#include "ShootingEvent.h"
#include "Renderer.h"

void ShootingEvent::runHandler(Renderer& renderer) {
    renderer.processEvent(*this);
};
