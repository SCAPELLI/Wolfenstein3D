
#include "common/include/EventSerializer.h"
#include "CreateMapEvent.h"

CreateMapEvent::CreateMapEvent(updateEventType eventType, int width, int height)
: eventType(eventType), width(width), height(height){}

void CreateMapEvent::addPlayer(int idPlayer, Vector& startingLocation) {
    startingLocations[idPlayer] = std::make_pair(startingLocation.x, startingLocation.y);
}

void CreateMapEvent::runHandler(CGame &renderer) {
    renderer.processEvent(*this);
}

updateEventType CreateMapEvent::getEventType() {
    return eventType;
}

std::string CreateMapEvent::getSerialization() {
    return EventSerializer::serialize(*this);

}