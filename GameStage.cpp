#include <iostream>
#include "GameStage.h"
#include "TurnEvent.h"
#include "MovementEvent.h"
#include "ProtectedEventsQueue.h"
#include "Event.h"
#include "ShootingEvent.h"
#include "LifeDecrementEvent.h"

void GameStage::processEvent(TurnEvent& event) {

    ShootingEvent s;
    Event updateEvent(&s, ShootingEventType);
    updateEvents.push(updateEvent);

    std::cout<<"Turn!"<<std::endl;
}
void GameStage::processEvent(MovementEvent& event) {

    LifeDecrementEvent l;

    Event anotherEvent(&l, LifeDecrementEventType);
    updateEvents.push(anotherEvent);

    std::cout<<"Move!"<<std::endl;
}
