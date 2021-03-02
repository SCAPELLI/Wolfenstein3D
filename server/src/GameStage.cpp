#include <iostream>
#include <common/ServerEvents/SpawnEvent.h>
#include <common/ServerEvents/ChangeWeaponEvent.h>
#include <common/ServerEvents/AmmoChangeEvent.h>
#include "server/include/GameStage.h"
#include "common/include/TurnEvent.h"
#include "common/include/MovementEvent.h"
#include "common/include/ProtectedEventsQueue.h"
#include "common/include/Event.h"
#include "common/include/ShootingEvent.h"
#include "common/ServerEvents/KillEvent.h"
#include "common/include/EventSerializer.h"
#include "common/ServerEvents/PositionEvent.h"
#include "common/ServerEvents/GameOverEvent.h"
#include "common/ServerEvents/HealthChangeEvent.h"
#include "common/include/OpenDoorEvent.h"
#include "common/ServerEvents/SpawnEvent.h"
#include "server/include/PlayerInfo.h"
#include "common/include/BlockingEventsQueue.h"
#include <algorithm>
#include <common/ServerEvents/DoorOpenedEvent.h>

#define PI 3.141592


GameStage::GameStage(std::vector<BlockingEventsQueue>* queues,
                     std::map<int, std::string>& playersNames, int levelId, char* configPath)
    : queues(queues), newEvents() {
    game = Game(newEvents, playersNames, levelId, configPath);
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
    AmmoChangeEvent ammo(AmmoChangeType, event.idPlayer, game.getBullets(event.idPlayer));
    Event ammoEvent(&ammo, AmmoChangeType);
    Message msgAmmo(EventSerializer::serialize(ammoEvent));
    ShootingEvent shoot(event.idPlayer);
    Event anotherEvent(&shoot, ShootingEventType);
    Message msgShoot(EventSerializer::serialize(anotherEvent));
    for (int i = 0; i < queues->size(); i++) {
        queues->at(i).push(msgShoot);
        queues->at(i).push(msgAmmo);
    }
    if (idHit == -3) {
        ChangeWeaponEvent newEvent(event.idPlayer, 0);
        Event anotherEvent(&newEvent, ChangeWeaponType);
        Message msg(EventSerializer::serialize(anotherEvent));
        for (int i = 0; i < queues->size(); i++){
            queues->at(i).push(msg);
        }
        return;
    }
    pushNewEvents();
}

void GameStage::processEvent(MovementEvent& event) {
    Vector movement = game.calculateDirection(event.idPlyr);
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
        delete newEvents[i];
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

void GameStage::processEvent(QuitEvent& quitEvent) {
    std::map<std::string, std::vector<int>> names;
    game.getHighscores(names);

    quitEvent.highscore = names;

    KillEvent killEvent(KillEventType, quitEvent.playerId);
    Message msg1 = EventSerializer::serialize(killEvent);
    std::string msg2 = EventSerializer::serialize(quitEvent);
    for (int j = 0; j < queues->size(); j++) {
        queues->at(j).push(msg1);
        queues->at(j).push(msg2);
    }
}

bool GameStage::gameFinished() {
    return game.GameFinished();
}

void GameStage::ifSomeoneWinNotifyHim() {
    bool gameFinished = game.GameFinished();

    if (!gameFinished) return;

    int winnerId = game.getWinnerId();
    std::map<std::string, std::vector<int>> names;
    game.getHighscores(names);

    GameOverEvent gameOverEvent(GameOverEventType, winnerId, names);
    Message msg1(EventSerializer::serialize(gameOverEvent));

    for (auto &queue: *queues)
        queue.push(msg1);
}