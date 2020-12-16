#include "Game.h"
#include "Vector.h"
#include "GameLoader.h"
#include <cmath>
#include <iostream>

#define DAMAGE 25


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
            if (players[i].lifeDecrement(
                    players[idPlayer].damageCurrentWeapon()) == -1)
                return i;// devuelve -1 es game over de ese jug
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
int Game::decrementLife(int idPlyr) {  //fijarme tipo de arma actual o no...
    int damage = players[idPlyr].lifeDecrement(DAMAGE);
    if (damage == -1)
        return idPlyr;
}
