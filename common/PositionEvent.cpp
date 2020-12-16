#include "PositionEvent.h"

void PositionEvent::runHandler(CGame& game) {
    game.processEvent(*this);
};
PositionEvent::PositionEvent(double x, double y):
        x(x), y(y){}
