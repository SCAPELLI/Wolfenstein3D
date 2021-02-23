#include "Game.h"
#include "Vector.h"
#include "GameLoader.h"
#include "../common/ServerEvents/PositionEvent.h"
#include "../common/ServerEvents/KillEvent.h"
#include "../common/ServerEvents/HealthChangeEvent.h"
#include "../common/ServerEvents/GameOverEvent.h"
#include "../common/ServerEvents/ChangeWeaponEvent.h"
#include "../common/ServerEvents/SpawnEvent.h"
#include "../common/ServerEvents/CreateMapEvent.h"
#include <vector>
#include "WallRay.h"
#include <cmath>



Game::Game( std::vector<AbstractEvent*>& newEvents,
            std::map<int, std::string>& playersNames, int levelId)
            :     levelId(levelId){
    GameLoader yaml;
    yaml.readData(speed);
    int cont = 0;
    for (auto it=playersNames.begin(); it!=playersNames.end(); ++it){
        ids[it->first] = cont;
        players.emplace_back(Player(it->first, cont, it->second, Vector(0, 0)));
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
                  cos(players[ids[idPlayer]].getAngle())) * speed;
}

void Game::moveAngle(double angle, int idPlayer){
    players[ids[idPlayer]].rotate(angle);
}
int Game::getDamage(int idPlayer){
    return players[ids[idPlayer]].damageCurrentWeapon();
}

int Game::shoot(int idPlayer, std::vector<AbstractEvent*>& newEvents){
    if (!players[ids[idPlayer]].canShoot()){
        return -2;
    }
    if (!players[ids[idPlayer]].shoot()) {
        return -3;
    }
    WallRay ray = WallRay(players[ids[idPlayer]].getPosition(), players[ids[idPlayer]].getAngle());
    int distanceToWall = ray.distanceToWall(map);
    if (players[ids[idPlayer]].hasRocketLauncher()){
        Rocket* rocket = players[ids[idPlayer]].setRocket();
        Vector shotDirection = calculateDirection(idPlayer) / speed;
        map.launchRocket(rocket, shotDirection, newEvents);
        return -1;
    }
    for (int i = 0; i < players.size(); i++){
        if ( i == idPlayer)
            continue;
        int distancePlayer = players[ids[idPlayer]].distanceWith(players[i]);
        if (distancePlayer < distanceToWall) {
            if (!canShoot(idPlayer, i))
                continue;
            int damage = players[ids[idPlayer]].hits(players[i]) + 70;
            int newHp = players[i].getDamage(damage);
            if (players[i].isGameOver()) {
                players[ids[idPlayer]].updateKills();
                map.dropAllItems(players[i], newEvents);
                std::map<std::string, std::vector<int>> highscores;
                getHighscores(highscores);
                AbstractEvent *event = new GameOverEvent(GameOverEventType,
                                                         ids[i], highscores);
                newEvents.push_back(event);
            }
            else if (players[i].isDead()){
                players[ids[idPlayer]].updateKills();
                AbstractEvent* event = new KillEvent(KillEventType, players[i].getId());
                newEvents.push_back(event);
                map.dropAllItems(players[i], newEvents);
                respawnPlayer(players[i].getId(), newEvents);
            }
            else{
                AbstractEvent* event = new HealthChangeEvent(HealthChangeType,
                                                             players[i].getId(), newHp);
                newEvents.push_back(event);
            }
            return i;// devolves a quien le pegaste
        }
    }
    return -1;
}
//
//bool Game::reactToDamage(int damaged, int sender,std::vector<AbstractEvent*>& newEvents ){
//    if (players[damaged].isGameOver()) {
//        players[ids[sender]].updateKills();
//        map.dropAllItems(players[damaged], newEvents);
//        std::map<std::string, std::vector<int>> highscores;
//        getHighscores(highscores);
//        AbstractEvent *event = new GameOverEvent(GameOverEventType,
//                                                 ids[damaged], highscores);
//        newEvents.push_back(event);
//    }
//    else if (players[damaged].isDead()){
//        players[ids[sender]].updateKills();
//        AbstractEvent* event = new KillEvent(KillEventType, ids[damaged]);
//        newEvents.push_back(event);
//        map.dropAllItems(players[damaged], newEvents);// borrar directamente player aca?
//        respawnPlayer(ids[damaged], newEvents);
//    }
//    else{
//        AbstractEvent* event = new HealthChangeEvent(HealthChangeType, players[damaged].getHealth());
//        newEvents.push_back(event);
//    }
//}

void Game::getHighscores(std::map<std::string, std::vector<int>>& names){
    std::vector<int> highscores;
    for (int i = 0; i < players.size(); i++){
        highscores.push_back(players[i].getBulletsShoot());
        highscores.push_back(players[i].getEnemiesKilled());
        highscores.push_back(players[i].getScore());
        names[players[i].getName()] = highscores;
        highscores.clear();
    }
    return;
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

void Game::increaseCooldown() {
    map.increaseCooldown();
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

