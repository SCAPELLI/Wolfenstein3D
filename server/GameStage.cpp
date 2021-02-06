#include <iostream>
#include <ServerEvents/SpawnEvent.h>
#include "GameStage.h"
#include "../common/TurnEvent.h"
#include "../common/MovementEvent.h"
#include "../common/ProtectedEventsQueue.h"
#include "../common/Event.h"
#include "GameLoader.h"
#include "../common/ShootingEvent.h"
#include "ServerEvents/KillEvent.h"
#include "ServerEvents/PositionEvent.h"
#include "ServerEvents/GameOverEvent.h"
#include "../common/OpenDoorEvent.h"
#include "ServerEvents/SpawnEvent.h"

#define PI 3.141592

GameStage::GameStage(ProtectedEventsQueue& updateEvents)
    : updateEvents(updateEvents), game(), newEvents() {}

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
        KillEvent decreasedLife(idHit);
        processEvent(decreasedLife);
        Event anotherEvent(&decreasedLife, KillEventType);
        updateEvents.push(anotherEvent);
    }
}

void GameStage::processEvent(MovementEvent& event) {
    Vector movement = game.calculateDirection(event.idPlyr);
    std::cout << "SERVER\n";
    std::cout << movement.x << "," << movement.y << "\n";
    switch (event.getDirection()) {
        case BACKWARD: {
            game.changePosition(movement * -1, event.idPlyr, newEvents);
            break;
        }
        case FORWARD: {
            game.changePosition(movement, event.idPlyr, newEvents);
            break;
        }
        default:
            break;
    }
//    PlayerEvent toSend;
//    listOfEvents.toYaml()
//    push(yaml)
    PositionEvent toSend(game.players[event.idPlyr].getId(),
                         game.players[event.idPlyr].getPosition().x,
                         game.players[event.idPlyr].getPosition().y);
    Event anotherEvent(&toSend, PositionEventType);
    updateEvents.push(anotherEvent);
}

void GameStage::processEvent(KillEvent& event){ //no
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
    OpenDoorEvent toSend(event.idPlayer, false); //id puerta
    if (game.openTheDoor(event.idPlayer, newEvents)) {
        toSend.changeStatusDoor(true);
    }
    Event anotherEvent(&toSend, OpenDoorType);
    updateEvents.push(anotherEvent);
}

void GameStage::processEvent(int objId, int type, int posX, int posY) {
    SpawnEvent toSend(objId, type, posX, posY);
    Event anotherEvent(&toSend, SpawnEventType);
    updateEvents.push(anotherEvent);
}
void GameStage::IncrementCooldown(){
    game.increaseCooldown();
}