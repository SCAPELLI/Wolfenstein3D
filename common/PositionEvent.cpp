#include "PositionEvent.h"
#include "EventSerializer.h"

void PositionEvent::runHandler(CGame& game) {
    game.processEvent(*this);
};
PositionEvent::PositionEvent(double x, double y):
        x(x), y(y), playerId(0){}

PositionEvent::PositionEvent(int playerId, double x, double y):
        x(x), y(y), playerId(playerId){}

std::string PositionEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}