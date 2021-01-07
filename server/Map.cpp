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


Map::Map()
 // crear vector de vectores
{
    std::vector<std::vector<CellMap>> map;
    std::vector<Player> players;
    YAML::Node config = YAML::LoadFile("map.yaml");
    YAML::Node matrixConfig = config["map"];
    int numOfPlayer = 0;
    for (std::size_t i = 0; i < matrixConfig.size(); i++) {
        std::vector<CellMap> row;
        for (std::size_t j = 0; j < matrixConfig[i].size(); j++) {
            int elem = matrixConfig[i][j].as<int>();
            if (elem == PLAYER_ID) {
                Player newPlayer = Player(numOfPlayer, Vector(i * TILE, j * TILE));
                players.emplace_back(Player(numOfPlayer,   // players lo conviene tener map o game??
                                            Vector(i * TILE, j * TILE)));
                numOfPlayer++;
                CellMap position = CellMap();
                position.addPlayer(&newPlayer);
                row.push_back(position);
            } else if (elem) {
                CellMap position = CellMap();
                position.setSolid();
                row.push_back(position);
            }
        }
        map.push_back(row);
    }
    matrix = map;
}


std::vector<std::vector<CellMap>>& Map::getMatrix() {
    return matrix;
}

bool Map::isOkToMove(Vector& newPos){
    return !matrix[newPos.x][newPos.y].isSolid() && !matrix[newPos.x][newPos.y].hasPlayer();
}


 void Map::changePosition(Vector newPos, Vector oldPos){
    matrix[oldPos.x][oldPos.y].transferPlayer(matrix[newPos.x][newPos.y]);
    //checkear afuera por items y vaciarlos en ese caso!!!!!
}
