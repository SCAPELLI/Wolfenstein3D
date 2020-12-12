#include "PositionEvent.h"
#include "Renderer.h"

void PositionEvent::runHandler(Renderer& renderer) {
    renderer.processEvent(*this);
};

PositionEvent::PositionEvent(PositionEvent& updateEvent){}

PositionEvent::PositionEvent(int x, int y){}
