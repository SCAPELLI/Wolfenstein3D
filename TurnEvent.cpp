#include "TurnEvent.h"
#include "GameStage.h"

void TurnEvent::runHandler(GameStage& gameStage) {
    gameStage.processEvent(*this);
}

TurningSense TurnEvent::getSense(){
    return this->sense;
}

int TurnEvent::getDegrees(){
    return this->degrees;
}