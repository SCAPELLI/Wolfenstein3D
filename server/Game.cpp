#include "Game.h"
#include "Vector.h"
#include "GameLoader.h"
#include "ServerEvents/PositionEvent.h"
#include "ServerEvents/KillEvent.h"
#include "ServerEvents/HealthChangeEvent.h"
#include "ServerEvents/GameOverEvent.h"
#include <vector>
#include "WallRay.h"
#include <cmath>
#include <iostream>
#include <random>
#include <vector>


Game::Game( std::vector<AbstractEvent*>& newEvents,
            std::vector<std::string>& playersNames){
    GameLoader yaml;
    yaml.readData(speed);
    for (int i = 0; i < playersNames.size(); i++){
        players.emplace_back(Player(i, playersNames[i], Vector(0, 0)));
    }
    map = Map(players, newEvents);
}

Game::Game() {}

// int Game::generateRandom(){
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<int> distr(1, 10);
//     return distr(gen);
// }

Vector Game::calculateDirection(int idPlayer){
    return Vector(-sin(players[idPlayer].getAngle()),
                  cos(players[idPlayer].getAngle())) * speed;
}

void Game::moveAngle(double angle, int idPlayer){
    players[idPlayer].rotate(angle);
}
int Game::getDamage(int idPlayer){
    return players[idPlayer].damageCurrentWeapon();
}

int Game::shoot(int idPlayer, std::vector<AbstractEvent*>& newEvents){
    WallRay ray = WallRay(players[idPlayer].getPosition(), players[idPlayer].getAngle());
    int distanceToWall = ray.distanceToWall(map);
    if (players[idPlayer].hasRocketLauncher()){
        Rocket* rocket = players[idPlayer].setRocket();//ver tema speed
        Vector shotDirection = calculateDirection(idPlayer) / speed;
        map.launchRocket(rocket, shotDirection, newEvents);
        return 0;
    }
    for (int i = 0; i < players.size(); i++){
        if ( i == idPlayer)
            continue;
        int distancePlayer = players[idPlayer].distanceWith(players[i]);
        if (distancePlayer < distanceToWall) {
            if (!canShoot(idPlayer, i)) return -2;
            int damage = players[idPlayer].hits(players[i]);
            players[i].getDamage(damage);
            if (players[i].isGameOver()) {
                players[idPlayer].updateKills();
                AbstractEvent *event = new GameOverEvent(GameOverEventType, i);
                newEvents.push_back(event);
            }
            else if (players[i].isDead()){
                players[idPlayer].updateKills();
                AbstractEvent* event = new KillEvent(KillEventType, i);
                newEvents.push_back(event);
                respawnPlayer(i);
            }
            else{
                AbstractEvent* event = new HealthChangeEvent(HealthChangeType, damage);
                newEvents.push_back(event);
            }
            return i;// devolves a quien le pegaste
        }
    }
    return -2;
}

bool Game::changeWeapon(int idPlayer, int idWeapon) {
    return players[idPlayer].changeWeaponTo(idWeapon);
}

void Game::changePosition(Vector changeTo, int idPlayer,
                                   std::vector<AbstractEvent*>& newEvents){
    idPlayer = 0;
    Vector futurePos = (players[idPlayer].getPosition() + changeTo).scale();
    if (map.isOkToMove(futurePos)){
        map.changePosition(futurePos, players[idPlayer], newEvents);
        players[idPlayer].move(changeTo);
        newEvents.push_back(new PositionEvent(PositionEventType,
                                              idPlayer, players[idPlayer].getPosition().x,
                                              players[idPlayer].getPosition().y));
    }
}


bool Game::openTheDoor(int idPlayer, std::vector<AbstractEvent*>& newEvents){
    return map.isADoor(players[idPlayer], newEvents);
}

void Game::increaseCooldown() {
    map.increaseCooldown();
    for (int i = 0; i < players.size(); i++) {
        players[i].incrementCooldown();
    }
}

bool Game::canShoot(int idPlayer, int otherPlayerId){
    return players[idPlayer].canShoot(players[otherPlayerId]);
}

void Game::respawnPlayer(int idPlayer){
    players[idPlayer].respawn();
}