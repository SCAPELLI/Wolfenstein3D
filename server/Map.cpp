#include "Map.h"
#include <yaml-cpp/yaml.h>
#include "Player.h"
#include <random>
#include <vector>
#include <iostream>
#define WALL 2
#define PLAYER_ID 1


Map::Map(std::vector<int> matrix)
: matrix(matrix)
{}


std::vector<int>& Map::getMatrix() {
    return matrix;
}

