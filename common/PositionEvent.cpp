#include "PositionEvent.h"
#include "Renderer.h"

void PositionEvent::runHandler(Renderer& renderer) {
    renderer.processEvent(*this);
};
