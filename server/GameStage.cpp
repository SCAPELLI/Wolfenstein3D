#include <iostream>
#include "GameStage.h"
#include "../common/TurnEvent.h"
#include "../common/MovementEvent.h"
#include "../common/ProtectedEventsQueue.h"
#include "../common/Event.h"
#include "GameLoader.h"
#include "../common/ShootingEvent.h"
#include "../common/LifeDecrementEvent.h"
#include "../common/PositionEvent.h"
#include "../common/GameOverEvent.h"


GameStage::GameStage(ProtectedEventsQueue& updateEvents)
    : updateEvents(updateEvents), game() {

}

void GameStage::processEvent(TurnEvent& event) {
    ShootingEvent s(0);
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
    LifeDecrementEvent l(0, 10);
    //LifeDecrementEvent event(...)
    Event anotherEvent(&l, LifeDecrementEventType);
    //event->assign()

}

void GameStage::processEvent(MovementEvent& event) {
    int x,y;
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
    PositionEvent toSend(game.players[0].getPosition().x, game.players[0].getPosition().y);

    Event anotherEvent(&toSend, LifeDecrementEventType);
    updateEvents.push(anotherEvent);
    std::cout<<game.players[0].getPosition().x<<std::endl;
    std::cout<<game.players[0].getPosition().y<<std::endl;
}

void GameStage::processEvent(LifeDecrementEvent& event){
    if (game.decrementLife(0) == -1){ //pasarle un ID PLYR
        GameOverEvent dead(0);
        Event anotherEvent(&dead, GameOverEventType);
        updateEvents.push(anotherEvent);
    }
}

void processEvent(GameOverEvent& event){}