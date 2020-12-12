#include "LifeDecrementEvent.h"
#include "Renderer.h"

void LifeDecrementEvent::runHandler(Renderer& renderer) {
    renderer.processEvent(*this);
};
