#include "Game.h"
#include "Vector.h"
#include "GameLoader.h"

#include <cmath>
# define M_PIl

#define DAMAGE 25
#define SPEED 5

Game::Game(){
    GameLoader yaml;
    yaml.readData(map, players);
}


//Game::Game(Game &&other): map(other.map), players(other.player) {}

//Game& Game::operator=(Game &&other)noexcept{
//    this->map = other.map;
//    this->player = other.player;
//    return *this;
//}
//
Vector Game::calculateDirection(int idPlyr){
    return Vector(cos(players[idPlyr].getAngle()), sin(players[idPlyr].getAngle())) * SPEED;
}

void Game::moveAngle(double angle){
    players[0].rotate(angle);
}

void Game::changePosition(Vector changeTo){
    Vector futurePos = (players[0].getPosition() + changeTo).scale();
    if (map[futurePos.x][futurePos.y] == 0){
        players[0].move(changeTo);
    }
}
int Game::decrementLife(int idPlyr) {  //fijarme tipo de arma actual
    int damage = players[idPlyr].lifeDecrement(DAMAGE);
    if (damage == -1)
        return -1;
}
