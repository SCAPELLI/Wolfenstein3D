#include "common/include/MovementEvent.h"
#include "server/include/GameStage.h"
#include "common/include/EventSerializer.h"

void MovementEvent::runHandler(GameStage& gameStage) {
    gameStage.processEvent(*this);
}
std::string MovementEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}
MovementDirection MovementEvent::getDirection(){
    return this->direction;
}
