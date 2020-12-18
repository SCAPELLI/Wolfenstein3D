#include "Game.h"
#include "Vector.h"
#include "GameLoader.h"
#include <cmath>
#include <iostream>


Game::Game(){
    GameLoader yaml;
    yaml.readData(map, players, speed);
}


Vector Game::calculateDirection(int idPlyr){
    return Vector(cos(players[idPlyr].getAngle()),
                  sin(players[idPlyr].getAngle())) * speed;
}

void Game::moveAngle(double angle, int idPlayer){
    players[idPlayer].rotate(angle);
}
int Game::getDamage(int idPlyr){
    return players[idPlyr].damageCurrentWeapon();
}

int Game::shoot(int idPlayer, int idWeapon, Vector& direction){
    for (int i = 0; i < players.size(); i++){
        if ( i == idPlayer)
            continue;
        if (players[idPlayer].hits(players[i])){
            players[i].lifeDecrement(players[idPlayer].damageCurrentWeapon());
            if (players[i].isGameOver())
                return i;// activas que se murio ese wacho
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
void Game::decrementLife(int idPlyr) {
    players[idPlyr].lifeDecrement(players[idPlyr].damageCurrentWeapon());
    if (players[idPlyr].isGameOver())
        return;
}


