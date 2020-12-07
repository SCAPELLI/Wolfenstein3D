#include <iostream>
#include "GameStage.h"
#include "TurnEvent.h"
#include "MovementEvent.h"
#include "ProtectedEventsQueue.h"
#include "Event.h"

void GameStage::processEvent(TurnEvent& event) {
    Event updateEvent(Shooting);
    updateEvents.push(updateEvent);

    std::cout<<"Turn!"<<std::endl;
}
void GameStage::processEvent(MovementEvent& event) {

    Event anotherEvent(LifeDecrement);
    updateEvents.push(anotherEvent);

    std::cout<<"Move!"<<std::endl;
}
