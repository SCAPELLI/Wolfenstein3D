#include "PositionEvent.h"
#include "common/include/EventSerializer.h"

void PositionEvent::runHandler(CGame& game) {
    game.processEvent (*this);
};
PositionEvent::PositionEvent (updateEventType eventType, int idPlayer, double x, double y):
        playerId(idPlayer), x(x), y(y), eventType(eventType){}


updateEventType PositionEvent::getEventType() {
    return eventType;
}

std::string PositionEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}