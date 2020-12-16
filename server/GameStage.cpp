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

#define PI 3.141592

GameStage::GameStage(ProtectedEventsQueue& updateEvents)
    : updateEvents(updateEvents), game() {}

void GameStage::processEvent(TurnEvent& event) {
    game.moveAngle(event.getDegrees(), event.player);
    TurnEvent toSend(0, event.getDegrees());
    Event anotherEvent(&toSend, TurnEventType);
    updateEvents.push(anotherEvent);
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
}

void GameStage::processEvent(LifeDecrementEvent& event){
    if (game.decrementLife(0) == -1){ //pasarle un ID PLYR
        GameOverEvent dead(0);
        Event anotherEvent(&dead, GameOverEventType);
        updateEvents.push(anotherEvent);
    }
}

void processEvent(GameOverEvent& event){}