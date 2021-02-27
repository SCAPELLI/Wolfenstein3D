#include <iostream>
#include <../common/ServerEvents/SpawnEvent.h>
#include <../common/ServerEvents/ChangeWeaponEvent.h>
#include <../common/ServerEvents/AmmoChangeEvent.h>
#include "GameStage.h"
#include "../common/TurnEvent.h"
#include "../common/MovementEvent.h"
#include "../common/ProtectedEventsQueue.h"
#include "../common/Event.h"
#include "../common/ShootingEvent.h"
#include "../common/ServerEvents/KillEvent.h"
#include "../common/EventSerializer.h"
#include "../common/ServerEvents/PositionEvent.h"
#include "../common/ServerEvents/GameOverEvent.h"
#include "../common/ServerEvents/HealthChangeEvent.h"
#include "../common/OpenDoorEvent.h"
#include "../common/ServerEvents/SpawnEvent.h"
#include "PlayerInfo.h"
#include "../common/BlockingEventsQueue.h"
#include <algorithm>
#define PI 3.141592


GameStage::GameStage(std::vector<BlockingEventsQueue>* queues,
                     std::map<int, std::string>& playersNames, int levelId)
    : queues(queues), newEvents() {
    game = Game(newEvents, playersNames, levelId);
    pushNewEvents();
}

void GameStage::processEvent(TurnEvent& event) {
    game.moveAngle(event.getDegrees(), event.idPlayer);
    TurnEvent toSend(event.idPlayer, event.getDegrees());
    Event anotherEvent(&toSend, TurnEventType);
    Message msg(EventSerializer::serialize(anotherEvent));
    for(int i = 0; i < queues->size(); i++){
        queues->at(i).push(msg);
    }
}

void GameStage::processEvent(ShootingEvent& event) {
    int idHit = game.shoot(event.idPlayer, newEvents);
    if (idHit == -2) return;
    if (idHit == -3) {
        ChangeWeaponEvent newEvent(event.idPlayer, 0);
        Event anotherEvent(&newEvent, ChangeWeaponType);
        Message msg(EventSerializer::serialize(anotherEvent));
        for (int i = 0; i < queues->size(); i++){
            queues->at(i).push(msg);
        }
        return;
    }

    AmmoChangeEvent ammo(AmmoChangeType, event.idPlayer,
                         -1 * game.players[game.ids[event.idPlayer]].getWeapon().minBullets);
    ShootingEvent shoot(event.idPlayer);
    Event anotherEvent(&shoot, ShootingEventType);
    Event ammoEvent(&ammo, AmmoChangeType);
    Message msgShoot(EventSerializer::serialize(anotherEvent));
    Message msgAmmo(EventSerializer::serialize(ammoEvent));
    for (int i = 0; i < queues->size(); i++){
        queues->at(i).push(msgShoot);
        queues->at(i).push(msgAmmo);
    }
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
        Message msg(EventSerializer::serialize(anotherEvent));
        for (int j = 0; j < queues->size(); j++) {
            queues->at(j).push(msg);
        }
    }
    newEvents.clear();
}


void GameStage::processEvent(OpenDoorEvent& event){
    if (game.openTheDoor(event.idPlayer, newEvents)) {
        pushNewEvents();
    }
}

void GameStage::processEvent(ChangeWeaponEvent& event){
    if (!game.changeWeapon(event.idPlayer, event.type)) return;

    Event anotherEvent(&event, ChangeWeaponType);
    Message msg(EventSerializer::serialize(anotherEvent));
    for (int i = 0; i < queues->size(); i++){
        queues->at(i).push(msg);
    }

}


void GameStage::processEvent(int objId, int type, int posX, int posY) {
    SpawnEvent toSend(SpawnEventType, objId, type, posX, posY);
    Event anotherEvent(&toSend, SpawnEventType);
    Message msg(EventSerializer::serialize(anotherEvent));
    for (int i = 0; i < queues->size(); i++){
        queues->at(i).push(msg);
    }
}

void GameStage::incrementCooldown(){
    game.increaseCooldown();
}

std::vector<PlayerInfo> GameStage::getPlayersInfo(){
    std::vector<PlayerInfo> playersInfo;
    for (int i = 0; i < game.players.size(); i++){
        PlayerInfo playerInfo;
        playerInfo.idPlayer = game.players[i].getId();
        double anglePlayer = game.players[i].getAngle();
        if (anglePlayer < 0)
           anglePlayer = anglePlayer + 2*PI;
        playerInfo.angle =  anglePlayer;
        playerInfo.x =  (float)game.players[i].getPosition().x;
        playerInfo.y =  (float)game.players[i].getPosition().y;
        playerInfo.life =  game.players[i].getLifes();
        playersInfo.push_back(playerInfo);
    }
    return playersInfo;
}