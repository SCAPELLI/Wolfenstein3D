#include "Game.h"
#include "Vector.h"
#include "GameLoader.h"
#include "ServerEvents/PositionEvent.h"
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#define DAMAGEBULLET 1


Game::Game( std::vector<AbstractEvent*>& newEvents){
    GameLoader yaml;
    yaml.readData(speed);
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
    for (int i = 0; i < players.size(); i++){
        if ( i == idPlayer)
            continue;
        if (players[idPlayer].hits(players[i])) {
            Vector posPlayer = players[idPlayer].getPosition();
            double distance = posPlayer.distance(players[i].getPosition());
            double randomHit = generateRandom();
            players[i].KillEvent((int) ((DAMAGEBULLET * randomHit) / distance));
            return i;// devolves a quien le pegaste
        }
    }
    return -1;
}



void Game::changePosition(Vector changeTo, int idPlayer,
                                   std::vector<AbstractEvent*>& newEvents){
    idPlayer = 0;
    Vector futurePos = (players[idPlayer].getPosition() + changeTo).scale();
    if (map.isOkToMove(futurePos)){
        map.changePosition(futurePos, players[idPlayer], newEvents);
        newEvents.push_back(new PositionEvent(PositionEventType,
                                              idPlayer, players[idPlayer].getPosition().x,
                                              players[idPlayer].getPosition().y));
        players[idPlayer].move(changeTo);
    }
}

void Game::decrementLife(int idPlayer) {
    players[idPlayer].KillEvent(players[idPlayer].damageCurrentWeapon());
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
