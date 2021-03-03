#include "server/include/Game.h"
#include "server/include/Vector.h"
#include "server/include/GameLoader.h"
#include "common/ServerEvents/PositionEvent.h"
#include "common/ServerEvents/KillEvent.h"
#include "common/ServerEvents/HealthChangeEvent.h"
#include "common/ServerEvents/GameOverEvent.h"
#include "common/ServerEvents/ChangeWeaponEvent.h"
#include "common/ServerEvents/SpawnEvent.h"
#include "common/ServerEvents/CreateMapEvent.h"
#include <vector>
#include "server/include/WallRay.h"
#include <cmath>
#include <iostream>


Game::Game( std::vector<AbstractEvent*>& newEvents,
            std::map<int, std::string>& playersNames, int levelId, char* configPath)
            :     levelId(levelId){
    int cont = 0;
    for (auto it=playersNames.begin(); it!=playersNames.end(); ++it){
        ids[it->first] = cont;
        players.emplace_back(Player(it->first, cont, it->second, Vector(0, 0), configPath));
        cont++;
    }
    map = Map(players, newEvents ,levelId);
    auto startEvent = new CreateMapEvent(CreateMapType, map.getWidth(), map.getHeight());
    for (int i = 0; i < players.size(); i++){
        startEvent->addPlayer(players[i].getId(), players[i].getPosition());
    }
    newEvents.insert(newEvents.begin(), startEvent);
}

Game::Game() {}


Vector Game::calculateDirection(int idPlayer){
    return Vector(-sin(players[ids[idPlayer]].getAngle()),
                  cos(players[ids[idPlayer]].getAngle()))
                  * players[ids[idPlayer]].getSpeed();
}

void Game::moveAngle(double angle, int idPlayer){
    players[ids[idPlayer]].rotate(angle);
}
int Game::getBullets(int idPlayer){
    return players[ids[idPlayer]].getBullets();
}

int Game::shoot(int idPlayer, std::vector<AbstractEvent*>& newEvents){
    if (!players[ids[idPlayer]].canShoot()){
        return -2;
    }
    players[ids[idPlayer]].updateBullets();
    if (!players[ids[idPlayer]].hasToChangeWeapon()) {
        return -3;
    }
    WallRay ray = WallRay(players[ids[idPlayer]].getPosition(), players[ids[idPlayer]].getAngle());
    int distanceToWall = ray.distanceToWall(map);
    if (players[ids[idPlayer]].hasRocketLauncher()){ // hasActiveRocketLauncher
        Vector shotDirection = calculateDirection(idPlayer) / players[ids[idPlayer]].getSpeed();
        map.launchRocket(players[ids[idPlayer]], shotDirection, newEvents);
        return -1;
    }
    for (int i = 0; i < players.size(); i++){
        if ( i == ids[idPlayer])
            continue;
        WallRay rayWithOtherPlayer = WallRay(players[ids[idPlayer]].getPosition(), players[ids[idPlayer]].getAngle());
        int distancePlayer = players[ids[idPlayer]].distanceWith(players[i]);
        if (distancePlayer < distanceToWall) {
            if (!canShoot(idPlayer, i))
                continue;
            int damage = players[ids[idPlayer]].hits(players[i]);
            int newHp = players[i].getDamage(damage);
            reactToDamage(i, idPlayer, newEvents);
            return players[i].getId();// devolves a quien le pegaste
        }
    }
    return -1;
}

void Game::notifyAllDamageByRocket(int idPlayer, std::vector<AbstractEvent*>& newEvents){
    for (int i = 0; i < players.size(); i++){
        reactToDamage(i, idPlayer, newEvents);
    }
}

void Game::reactToDamage(int damaged, int sender,std::vector<AbstractEvent*>& newEvents ){
    if (players[damaged].isGameOver()) {
        players[ids[sender]].updateKills();
        map.dropAllItems(players[damaged], newEvents);
        std::map<std::string, std::vector<int>> highscores;
        getHighscores(highscores);
        AbstractEvent *event = new GameOverEvent(GameOverEventType,
                                                 players[damaged].getId(), highscores);
        newEvents.push_back(event);
    }
    else if (players[damaged].isDead()){
        players[ids[sender]].updateKills();
        AbstractEvent* event = new KillEvent(KillEventType, players[damaged].getId());
        newEvents.push_back(event);
        map.dropAllItems(players[damaged], newEvents);// borrar directamente player aca?
        respawnPlayer(players[damaged].getId(), newEvents);
    }
    else{
        AbstractEvent* event = new HealthChangeEvent(HealthChangeType,
                                                     players[damaged].getId(),
                                                     players[damaged].getHealth());
        newEvents.push_back(event);
    }
}

void Game::getHighscores(std::map<std::string, std::vector<int>>& names){
    for (int i = 0; i < players.size(); i++){
        std::vector<int> highscores;
        highscores.push_back(players[i].getBulletsShoot());
        highscores.push_back(players[i].getEnemiesKilled());
        highscores.push_back(players[i].getScore());
        names[players[i].getName()] = highscores;
    }

}
bool Game::changeWeapon(int idPlayer, int idWeapon) {
    return players[ids[idPlayer]].changeWeaponTo(idWeapon);
}

void Game::changePosition(Vector changeTo, int idPlayer,
                                   std::vector<AbstractEvent*>& newEvents){

    Vector futurePos = (players[ids[idPlayer]].getPosition() + changeTo).scale();
    if (map.isOkToMove(futurePos)){
        map.changePosition(futurePos, players[ids[idPlayer]], newEvents);
        players[ids[idPlayer]].move(changeTo);
        newEvents.push_back(new PositionEvent(PositionEventType,
                                              idPlayer, players[ids[idPlayer]].getPosition().x,
                                              players[ids[idPlayer]].getPosition().y));
    }
}


bool Game::openTheDoor(int idPlayer, std::vector<AbstractEvent*>& newEvents){
    return map.isADoor(players[ids[idPlayer]], newEvents);
}

void Game::increaseCooldown( std::vector<AbstractEvent*>& newEvents) {
    int idPlayer = map.increaseCooldown(newEvents);
    if (idPlayer != -1)
        notifyAllDamageByRocket(idPlayer, newEvents);
    for (int i = 0; i < players.size(); i++) {
        players[i].incrementCooldown();
    }
}

bool Game::canShoot(int idPlayer, int otherPlayerId){
    return players[ids[idPlayer]].doesHit(players[otherPlayerId]);
}

void Game::respawnPlayer(int idPlayer, std::vector<AbstractEvent*>& newEvents){
    Vector iniPos = players[ids[ idPlayer]].getInitialPosition().scale();
    map.changePosition(iniPos, players[ids[idPlayer]], newEvents);
    players[ids[idPlayer]].respawn();
}
bool Game::GameFinished() {
    int playersAlive = 0;
    for(auto& player: players) {
        if (player.getLifes()>0)
            ++playersAlive;
    }
    return playersAlive <= 1;
}

int Game::getWinnerId() {
    int playerId = 0;
    for(auto& player: players) {
        //bool asd = player.isGameOver();
        if (player.getLifes()>0)
            playerId = player.getId();
    }
    return playerId;
}