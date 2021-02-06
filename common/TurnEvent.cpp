#include "TurnEvent.h"
#include "EventSerializer.h"


void TurnEvent::runHandler(GameStage& gameStage) {
    gameStage.processEvent(*this);
}

void TurnEvent::runHandler(CGame& game){
    game.processEvent(*this);
}

double TurnEvent::getDegrees(){
    return this->degrees;
}

std::string TurnEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}