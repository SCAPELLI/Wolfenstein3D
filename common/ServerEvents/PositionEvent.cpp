#include "PositionEvent.h"
#include "../EventSerializer.h"

void PositionEvent::runHandler(CGame& game) {
    game.processEvent (*this);
};
PositionEvent::PositionEvent (updateEventType eventType, int idPlayer, double x, double y):
        x(x), y(y), eventType(eventType){}


updateEventType PositionEvent::getEventType() {
    return eventType;
}

std::string PositionEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}