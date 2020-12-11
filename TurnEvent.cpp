#include "TurnEvent.h"
#include "GameStage.h"
#include <iostream>

void TurnEvent::runHandler(GameStage& gameStage) {
    gameStage.processEvent(*this);
}

TurningSense TurnEvent::getSense(){
    return this->sense;
}

double TurnEvent::getDegrees(){
    std::cout << degrees;
    return this->degrees;
}