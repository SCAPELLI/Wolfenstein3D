

#include "Player.h"
#include <random>
#include "GameLoader.h"
#include "Game.h"
#include <vector>
#include <iostream>
#define WALL 2
#define PLAYER_ID 1
#define TILE 32

GameLoader::GameLoader() {}


void GameLoader::readData(std::vector<std::vector<int>>& map,
                          std::vector<Player>& players){
    YAML::Node config = YAML::LoadFile("map.yaml");
    YAML::Node matrix = config["map"];
    int length = config["length"].as<int>();
    int width = config["width"].as<int>();
    mapLoader(map, players, matrix);
}

void GameLoader::mapLoader(std::vector<std::vector<int>>& map,
                           std::vector<Player>& players, YAML::Node& matrix){
    for (std::size_t i = 0; i < matrix.size(); i++) {
        std::vector<int> row;
        for (std::size_t j = 0; j < matrix[i].size(); j++) {
            int elem = matrix[i][j].as<int>();
            if (elem == PLAYER_ID){
                players.emplace_back(PLAYER_ID,
                                     Vector (i * TILE, j * TILE));

            } else if (elem == WALL) {
                row.push_back(elem);
            } else {
                row.push_back(0);
            }
        }
        map.push_back(row);
    }
}

GameLoader::~GameLoader(){}