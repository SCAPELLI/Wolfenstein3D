#include "Game.h"
#include "Vector.h"
#include "GameLoader.h"
#include "ServerEvents/PositionEvent.h"
#include "WallRay.h"
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#define DAMAGEBULLET 1


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

 int Game::generateRandom(){
     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_int_distribution<int> distr(1, 10);
     return distr(gen);
 }

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

int Game::shoot(int idPlayer){
    WallRay ray = WallRay(players[idPlayer].getPosition(), players[idPlayer].getAngle());
    int distanceToWall = ray.distanceToWall(map);
    for (int i = 0; i < players.size(); i++){
        if ( i == idPlayer)
            continue;
        int distancePlayer = players[idPlayer].distanceWith(players[i]); //ver si es un jugador para el lado donde estoy mirando
        if (distancePlayer < distanceToWall) {
            //ver alguna forma que le diga si mato a alguien o no.
            players[idPlayer].hits(distancePlayer, players[idPlayer].getAngle()); // ojo que aca puse el angulo del jug no el angulo respecto a los jugs
            Vector posPlayer = players[idPlayer].getPosition();
            double distance = posPlayer.distance(players[i].getPosition());
            double randomHit = generateRandom();
            players[i].getDamage((int) ((DAMAGEBULLET * randomHit) / distance));
            return i;// devolves a quien le pegaste
        }
    }
    return -1;
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

void Game::decrementLife(int idPlayer) {
    players[idPlayer].getDamage(players[idPlayer].damageCurrentWeapon());
    if (players[idPlayer].isDead()) {
        map.dropAllItems(players[idPlayer]);
        map.removePlayer(players[idPlayer]);
        players[idPlayer].died();
        map.addPlayer(players[idPlayer]);
        return;
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
