#include <iostream>
#include <ServerEvents/SpawnEvent.h>
#include <ServerEvents/ChangeWeaponEvent.h>
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
    : updateEvents(updateEvents), newEvents(), playersNames() {
    for (int i = 0; i < 1; i++) {
        std::string name = "";
        playersNames.push_back(name);  // esto despues va a estar en el startGameEvent
    }
    game = Game(newEvents, playersNames);
}

//void GameStage::processEvent(StartGameEvent& event){


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
            GameOverEvent dead(GameOverEventType, idHit);
            Event anotherEvent(&dead, GameOverEventType);
            updateEvents.push(anotherEvent);
            return;
        }
        KillEvent decreasedLife(KillEventType, idHit);
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
    pushNewEvents();
}

void GameStage::pushNewEvents(){
    for (int (i) = 0; (i) < newEvents.size(); ++(i)) {
        Event anotherEvent(newEvents[i], newEvents[i]->getEventType());
        updateEvents.push(anotherEvent);
    }
    newEvents.clear();
}


void GameStage::processEvent(OpenDoorEvent& event){
    if (game.openTheDoor(event.idPlayer, newEvents)) {
        pushNewEvents();
    }
}

void GameStage::processEvent(ChangeWeaponEvent& event){
    if (game.changeWeapon(event.idPlayer, event.uniqueId)){
        Event anotherEvent(&event, ChangeWeaponType);
        updateEvents.push(anotherEvent);
    }
}


void GameStage::processEvent(int objId, int type, int posX, int posY) {
    SpawnEvent toSend(SpawnEventType, objId, type, posX, posY);
    Event anotherEvent(&toSend, SpawnEventType);
    updateEvents.push(anotherEvent);
}
void GameStage::IncrementCooldown(){
    game.increaseCooldown();
}