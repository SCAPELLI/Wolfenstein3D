

#include "CreateMapEvent.h"

CreateMapEvent::CreateMapEvent(updateEventType eventType, int width, int height)
: eventType(eventType), width(width), height(height){}

void CreateMapEvent::addPlayer(Vector startingLocation) {
    startingLocations.push_back(startingLocation);
}

void CreateMapEvent::runHandler(CGame &renderer) {
    renderer.processEvent(*this);
}

updateEventType CreateMapEvent::getEventType() {
    return eventType;
}