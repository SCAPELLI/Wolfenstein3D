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
#include "GameLoader.h"

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
            setElemInPosition(numOfPlayer, i , j, position, players, elem);
            row.push_back(position);
        }
        map.push_back(row);
    }
    matrix = map;
}

void Map::setElemInPosition(int numOfPlayer, int pos1, int pos2,
                            CellMap& tileMap, std::vector<Player>& players,
                            int elem){
    YAML::Node config = YAML::LoadFile("map.yaml");
    YAML::Node matrixConfig = config["map"];
    GameLoader yaml;
    if (elem == PLAYER_ID) {
        Player newPlayer = Player(numOfPlayer,
                                  Vector(pos1 * TILE, pos2 * TILE));
        players.emplace_back(newPlayer);
        numOfPlayer++;
        tileMap.addPlayer(newPlayer); // pasar a gameLoader el tile y que lo agregue

    } if (elem > 1 && elem < 100){
        tileMap.addItem(yaml.itemLoader(elem));
        return;
    }
    else if (elem >= 100 && elem < 200) {
        yaml.setTexture(elem, tileMap);
    }
}

std::vector<std::vector<CellMap>>& Map::getMatrix() {
    return matrix;
}
void Map::removePlayer(Player& player){
    Vector positionPlayer = player.getScaledPosition();
    matrix[positionPlayer.y][positionPlayer.x].removePlayer(player);
}
void Map::addPlayer(Player& player){
    Vector posScaled = Vector((player.getScaledPosition()));
    matrix[posScaled.y][posScaled.x].addPlayer(player);
}
bool Map::isOkToMove(Vector& futurePos){
    return !matrix[futurePos.y][futurePos.x].isSolid();
}

void Map::dropAllItems(Player& player){
    Vector positionPlayer = player.getScaledPosition();
    matrix[positionPlayer.y][positionPlayer.x].dropItems(player);
}

void Map::dropItemPlayer(Player& player, Item itemPlayer){
    Vector positionPlayer = player.getScaledPosition();
    matrix[positionPlayer.y][positionPlayer.x].dropItemPlayer(itemPlayer);
}

 void Map::changePosition(Vector& newPos, Player& player){ //???
     Vector positionPlayer = player.getScaledPosition();
     matrix[positionPlayer.y][positionPlayer.x].removePlayer(player);
     matrix[newPos.y][newPos.x].addPlayer(player);
     matrix[newPos.y][newPos.x].getItemsTile(player);
}
