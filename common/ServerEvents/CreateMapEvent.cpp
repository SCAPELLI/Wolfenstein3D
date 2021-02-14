

#include "CreateMapEvent.h"

CreateMapEvent::CreateMapEvent(int width, int height)
: width(width), height(height){}

void CreateMapEvent::runHandler(CGame &renderer) {
    renderer.processEvent(*this);
}