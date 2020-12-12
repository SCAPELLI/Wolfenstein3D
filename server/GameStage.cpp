#include <iostream>
#include "GameStage.h"
#include "../common/TurnEvent.h"
#include "../common/MovementEvent.h"
#include "../common/ProtectedEventsQueue.h"
#include "../common/Event.h"
#include "GameLoader.h"
#include "../common/ShootingEvent.h"
#include "../common/LifeDecrementEvent.h"


GameStage::GameStage(ProtectedEventsQueue& updateEvents)
    : updateEvents(updateEvents), game() {

}

void GameStage::processEvent(TurnEvent& event) {
    ShootingEvent s;
    Event updateEvent(&s, ShootingEventType);
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
    LifeDecrementEvent l;
    //LifeDecrementEvent event(...)
    Event anotherEvent(&l, LifeDecrementEventType);
    //event->assign()

}

void GameStage::processEvent(MovementEvent& event) {

    //Event anotherEvent(Position);
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
    LifeDecrementEvent l;

    Event anotherEvent(&l, LifeDecrementEventType);
    updateEvents.push(anotherEvent);
    std::cout<<game.players[0].getPosition().x<<std::endl;
    std::cout<<game.players[0].getPosition().y<<std::endl;
}

void GameStage::processEvent(LifeDecrementEvent& event){
    if (game.decrementLife(0) == 0){ //pasarle un ID PLYR
        LifeDecrementEvent l;
        Event anotherEvent(&l, LifeDecrementEventType);
        //Event updateEvent(GameOver);
        updateEvents.push(anotherEvent);
    }
}

void processEvent(GameOverEvent& event){}