#include "Game.h"
#include "Vector.h"
#include "GameLoader.h"
#include <cmath>
#include <iostream>
#include <random>
#define DAMAGEBULLET 1


Game::Game(){
    GameLoader yaml;
    yaml.readData(map, players, speed);
}

 int Game::generateRandom(){
     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_int_distribution<int> distr(1, 10);
     return distr(gen);
 }

Vector Game::calculateDirection(int idPlayer){
    return Vector(cos(players[idPlayer].getAngle()),
                  sin(players[idPlayer].getAngle())) * speed;
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
            players[i].lifeDecrement((int) ((DAMAGEBULLET * randomHit) / distance));
            return i;// devolves a quien le pegaste
        }
    }
    return -1;
}



void Game::changePosition(Vector changeTo){
    Vector futurePos = (players[0].getPosition() + changeTo).scale();
    if (map[futurePos.x][futurePos.y] == 0){
        players[0].move(changeTo);
    }
}
void Game::decrementLife(int idPlayer) {
    players[idPlayer].lifeDecrement(players[idPlayer].damageCurrentWeapon());
    if (players[idPlayer].isGameOver())
        return;
}


