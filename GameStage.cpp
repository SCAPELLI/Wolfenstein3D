#include <iostream>
#include "GameStage.h"
#include "TurnEvent.h"
#include "MovementEvent.h"

void GameStage::processEvent(TurnEvent& event) {
    std::cout<<"Turn!"<<std::endl;
}
void GameStage::processEvent(MovementEvent& event) {
    std::cout<<"Move!"<<std::endl;
}
