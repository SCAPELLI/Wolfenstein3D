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
    : updateEvents(updateEvents), game() {}

void GameStage::processEvent(TurnEvent& event) {
    game.moveAngle(event.getDegrees(), event.player);
    game.players[0].getItem(3);
    game.players[0].getItem(4);
    game.players[0].changeWeaponTo(2);
    std::cout<<game.getDamage(0)<<std::endl;
}

void GameStage::processEvent(MovementEvent& event) {
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
    Event anotherEvent(&toSend, PositionEventType);
    updateEvents.push(anotherEvent);

    std::cout<<(int)game.players[0].getPosition().x<<" ";
    std::cout<<(int)game.players[0].getPosition().y<<std::endl;
}

void GameStage::processEvent(LifeDecrementEvent& event){
    game.decrementLife(0);
    if (game.players[0].isGameOver()){ //pasarle un ID PLYR
        GameOverEvent dead(0);
        Event anotherEvent(&dead, GameOverEventType);
        updateEvents.push(anotherEvent);
    }
}

void processEvent(GameOverEvent& event){}