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
#include "../common/OpenDoorEvent.h"

#define PI 3.141592

GameStage::GameStage(ProtectedEventsQueue& updateEvents)
    : updateEvents(updateEvents), game() {}

void GameStage::processEvent(TurnEvent& event) {
    game.moveAngle(event.getDegrees(), event.idPlayer);
    TurnEvent toSend(event.idPlayer, event.getDegrees());
    Event anotherEvent(&toSend, TurnEventType);
    updateEvents.push(anotherEvent);
}


void GameStage::processEvent(ShootingEvent& event) {
    int idHit = game.shoot(event.idPlayer);
    if ( idHit != -1){
        if (game.players[idHit].isGameOver()){
            GameOverEvent dead(idHit);
            Event anotherEvent(&dead, GameOverEventType);
            updateEvents.push(anotherEvent);
            return;
        }
        LifeDecrementEvent decreasedLife(idHit);
        processEvent(decreasedLife);
        Event anotherEvent(&decreasedLife, LifeDecrementEventType);
        updateEvents.push(anotherEvent);
    }
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
    game.decrementLife(event.idPlayer);
    if (game.players[event.idPlayer].isGameOver()){
        GameOverEvent dead(event.idPlayer);
        Event anotherEvent(&dead, GameOverEventType);
        updateEvents.push(anotherEvent);
        return;
    }
}

void GameStage::processEvent(GameOverEvent& event){
    GameOverEvent dead(event.idPlayer);
    Event anotherEvent(&dead, GameOverEventType);
    updateEvents.push(anotherEvent);
}

void GameStage::processEvent(OpenDoorEvent& event){
    OpenDoorEvent toSend(event.idPlayer, false); //faltaria checkear si es especial o no
    if (game.openTheDoor(event.idPlayer)) {
        toSend.changeStatusDoor(true);
    }
    Event anotherEvent(&toSend, OpenDoorType);
    updateEvents.push(anotherEvent);
}

