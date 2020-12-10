#include "Game.h"
#include "Vector.h"
#include <iostream>

Game::Game(std::vector<std::vector<int>> map, Player player)
    : map(map), player(std::move(player)){

    }

Game::Game(Game &&other): map(other.map),player(other.player) {}

Game& Game::operator=(Game &&other)noexcept{
    this->map = other.map;
    this->player = std::move(other.player);
    return *this;
}
     


void Game::moveAngle(int angle){
    player.rotate(angle);
}

void Game::changePosition(int dx, int dy){
    Vector newPos = Vector(dx, dy);
    Vector plyrPos = std::move(player.getPosition());

    Vector futurePos = std::move(plyrPos + newPos);
    if (map[futurePos.getX()][futurePos.getY()] == 0){
        map[plyrPos.getX()][plyrPos.getY()] = 0;
        map[futurePos.getX()][futurePos.getY()] = 1;
        player.move(futurePos);
    }
}
void Game::decrementLife() {
    player.lifeDecrement(25);
}
