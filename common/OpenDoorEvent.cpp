
#include "OpenDoorEvent.h"
#include "Renderer.h"
#include "../cliente/CGame.h"
#include "EventSerializer.h"

OpenDoorEvent::OpenDoorEvent(int idPlayer, bool isOpen)
        :idPlayer(idPlayer), opened(isOpen){}

//OpenDoorEvent::OpenDoorEvent(OpenDoorEvent& openDoorEvent) {}

void OpenDoorEvent::changeStatusDoor(bool status){
    opened = status;
}
std::string OpenDoorEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}
void OpenDoorEvent::runHandler(CGame& game) {
    game.processEvent(*this);
};