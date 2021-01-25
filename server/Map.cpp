#include "Map.h"
#include <yaml-cpp/yaml.h>
#include "Player.h"
#include <random>
#include <vector>
#include <iostream>
#include "../common/CellMap.h"
#define WALL 2
#define PLAYER_ID 1
#define TILE 32

Map::Map(){}

Map::Map(std::vector<Player>& players){
    std::vector<std::vector<CellMap>> map;
    YAML::Node config = YAML::LoadFile("map.yaml");
    YAML::Node matrixConfig = config["map"];
    int numOfPlayer = 0;
    for (std::size_t i = 0; i < matrixConfig.size(); i++) {
        std::vector<CellMap> row;
        for (std::size_t j = 0; j < matrixConfig[i].size(); j++) {
            int elem = matrixConfig[i][j].as<int>();
            CellMap position = CellMap();
            if (elem == PLAYER_ID) {
                Player newPlayer = Player(numOfPlayer, Vector(j * TILE, i * TILE));
                players.emplace_back(newPlayer);
                numOfPlayer++;
                position.addPlayer(&newPlayer);
            } else if (elem) {
                position.setSolid();
            }
            row.push_back(position);
        }
        map.push_back(row);
    }
    matrix = map;
}


std::vector<std::vector<CellMap>>& Map::getMatrix() {
    return matrix;
}
void Map::removePlayer(Vector& positionPlayer){
    matrix[positionPlayer.y][positionPlayer.x].removePlayer();
}
void Map::addPlayer(Player* player){
    Vector posScaled = Vector((player->getPosition()).scale());
    matrix[posScaled.y][posScaled.x].addPlayer(player);
}
bool Map::isOkToMove(Vector& position){
    return !matrix[position.y][position.x].isSolid();
}

void Map::dropAllItems(Vector& position){
    matrix[position.y][position.x].dropItems();
}

void Map::dropItemPlayer(Vector& position, Item itemPlayer){
    matrix[position.y][position.x].dropItemPlayer(itemPlayer);
}

 void Map::changePosition(Vector& newPos, Vector& oldPos){
    matrix[oldPos.y][oldPos.x].transferPlayer(matrix[newPos.y][newPos.x]);
    matrix[newPos.y][newPos.x].getItemsTile();
}
