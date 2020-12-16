#include "TurnEvent.h"

void TurnEvent::runHandler(GameStage& gameStage) {
    gameStage.processEvent(*this);
}


double TurnEvent::getDegrees(){
    return this->degrees;
}