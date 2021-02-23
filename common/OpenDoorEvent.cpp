
#include "common/OpenDoorEvent.h"
#include "client/CGame.h"
#include "EventSerializer.h"
#include "server/GameStage.h"

OpenDoorEvent::OpenDoorEvent(int idPlayer, bool isOpen)
        :idPlayer(idPlayer), opened(isOpen){}

//OpenDoorEvent::OpenDoorEvent(OpenDoorEvent& openDoorEvent) {}

void OpenDoorEvent::changeStatusDoor(bool status){
    opened = status;
}
std::string OpenDoorEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}

void OpenDoorEvent::runHandler(GameStage& game) {
    game.processEvent(*this);
};