#include "TurnEvent.h"


void TurnEvent::runHandler(GameStage& gameStage) {
    gameStage.processEvent(*this);
}

void TurnEvent::runHandler(CGame& game){
    game.processEvent(*this);
}

double TurnEvent::getDegrees(){
    return this->degrees;
}