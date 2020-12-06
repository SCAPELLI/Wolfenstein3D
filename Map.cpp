#include "Map.h"
#include <yaml-cpp/yaml.h>
#include "Player.h"
#include <random>
#include <vector>
#include <iostream>
#define WALL 2
#define PLAYER_ID 1


Map::Map(std::vector<int> matrix, Player& player)
: matrix(matrix), player(player)
{}


std::vector<int>& Map::getMatrix() {
    return matrix;
}

bool Map::isOkToMove(Vector& newPos){
    Vector plyrPos = std::move(player.getPosition());
    Vector futurePos = std::move(plyrPos + newPos);
    return matrix[futurePos.getX(), futurePos.getY()] != 0;
}

void Map::changePosition(Vector& newPos){
    if(isOkToMove(newPos)){
        player.move(newPos);
    }
}
