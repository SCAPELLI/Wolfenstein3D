#include <iostream>
#include <ServerEvents/SpawnEvent.h>
#include <ServerEvents/ChangeWeaponEvent.h>
#include <ServerEvents/AmmoChangeEvent.h>
#include "GameStage.h"
#include "../common/TurnEvent.h"
#include "../common/MovementEvent.h"
#include "../common/ProtectedEventsQueue.h"
#include "../common/Event.h"
#include "../common/ShootingEvent.h"
#include "ServerEvents/KillEvent.h"
#include "ServerEvents/PositionEvent.h"
#include "ServerEvents/GameOverEvent.h"
#include "ServerEvents/HealthChangeEvent.h"
#include "../common/OpenDoorEvent.h"
#include "ServerEvents/SpawnEvent.h"
#include "PlayerInfo.h"

#define PI 3.141592
#define MAX_PLAYERS 2

GameStage::GameStage(ProtectedEventsQueue& updateEvents)
    : updateEvents(updateEvents), newEvents(), playersNames() {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        std::string name = "";
        playersNames.push_back(name);  // esto despues va a estar en el startGameEvent
    }
    game = Game(newEvents, playersNames);
    pushNewEvents();
}

//void GameStage::processEvent(StartGameEvent& event){}


void GameStage::processEvent(TurnEvent& event) {
    game.moveAngle(event.getDegrees(), event.idPlayer);
    TurnEvent toSend(event.idPlayer, event.getDegrees());
    Event anotherEvent(&toSend, TurnEventType);
    updateEvents.push(anotherEvent);
}


void GameStage::processEvent(ShootingEvent& event) {
    int idHit = game.shoot(event.idPlayer, newEvents);
    if (idHit == -2) return;
    if (idHit == -3){
        ChangeWeaponEvent newEvent(event.idPlayer, 0);
        Event anotherEvent(&newEvent, ChangeWeaponType);
        updateEvents.push(anotherEvent);
        return;
    }
    AmmoChangeEvent ammo(AmmoChangeType, -1 * game.players[event.idPlayer].getWeapon().minBullets);
    ShootingEvent shoot(event.idPlayer);
    Event anotherEvent(&shoot, ShootingEventType);
    updateEvents.push(anotherEvent);
    Event ammoEvent(&ammo, AmmoChangeType);
    updateEvents.push(ammoEvent);
    pushNewEvents();
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
    if (game.changeWeapon(event.idPlayer, event.type)){
        Event anotherEvent(&event, ChangeWeaponType);
        updateEvents.push(anotherEvent);
    }
}


void GameStage::processEvent(int objId, int type, int posX, int posY) {
    SpawnEvent toSend(SpawnEventType, objId, type, posX, posY);
    Event anotherEvent(&toSend, SpawnEventType);
    updateEvents.push(anotherEvent);
}

void GameStage::incrementCooldown(){
    game.increaseCooldown();
}

std::vector<PlayerInfo> GameStage::getPlayersInfo(){
    std::vector<PlayerInfo> playersInfo;
    for (int i = 0; i < game.players.size(); i++){
        PlayerInfo playerInfo;
        playerInfo.idPlayer = game.players[i].getId();
        playerInfo.angle =  game.players[i].getAngle();
        playerInfo.x =  (float)game.players[i].getPosition().x;
        playerInfo.y =  (float)game.players[i].getPosition().y;
        playerInfo.life =  game.players[i].getLifes();
        playersInfo.push_back(playerInfo);
    }
    return playersInfo;
}