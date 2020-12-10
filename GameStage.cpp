#include <iostream>
#include "GameStage.h"
#include "Game.h"
#include "TurnEvent.h"
#include "MovementEvent.h"
#include "ProtectedEventsQueue.h"
#include "Event.h"

void GameStage::processEvent(TurnEvent& event) {
    switch (event.getSense()) {
        case CLOCKWISE:
            game.moveAngle(event.getDegrees());
            break;
        case ANTICLOCKWISE:
            game.moveAngle(event.getDegrees());
            break;
        default:
            break;
    }

    Event updateEvent(Position);
    //event.assign()
    updateEvents.push(updateEvent);

    std::cout<<"Turn!"<<std::endl;
}
void GameStage::processEvent(MovementEvent& event) {

    Event anotherEvent(Position);

    switch (event.getDirection()) {
        case BACKWARD:
            game.changePosition(-1, 0);
            break;
        case FOWARD:
            game.changePosition(1, 0);
            break;
        default:
            break;
    }
    updateEvents.push(anotherEvent);
    std::cout<<"Move!"<<std::endl;
}

void GameStage::processEvent(LifeDecrementEvent& event){
    game.decrementLife();
}
