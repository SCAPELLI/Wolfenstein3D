#include <iostream>
#include "GameStage.h"
#include "TurnEvent.h"
#include "MovementEvent.h"
#include "ProtectedEventsQueue.h"
#include "Event.h"
#include "GameLoader.h"


GameStage::GameStage(ProtectedEventsQueue& updateEvents)
    : updateEvents(updateEvents), game() {

}

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
    //LifeDecrementEvent event(...)
    Event updateEvent(Position);
    //event->assign()
    updateEvents.push(updateEvent);

    std::cout<<"Turn!"<<std::endl;
}
void GameStage::processEvent(MovementEvent& event) {

    Event anotherEvent(Position);
    Vector movement = game.calculateDirection(event.idPlyr);
    switch (event.getDirection()) {
        case BACKWARD:
            game.changePosition(movement * -1);
            break;
        case FOWARD:
            game.changePosition(movement);
            break;
        default:
            break;
    }
    updateEvents.push(anotherEvent);
    std::cout<<game.players[0].getPosition().x<<std::endl;
    std::cout<<game.players[0].getPosition().y<<std::endl;
}

void GameStage::processEvent(LifeDecrementEvent& event){
    if (game.decrementLife(0) == 0){ //pasarle un ID PLYR
        Event updateEvent(GameOver);
        updateEvents.push(updateEvent);
    }
}

void processEvent(GameOverEvent& event){}