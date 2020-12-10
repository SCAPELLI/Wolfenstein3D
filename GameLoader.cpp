

#include "Player.h"
#include <random>
#include "GameLoader.h"
#include "Game.h"
#include <vector>
#include <iostream>
#define WALL 2
#define PLAYER_ID 1

GameLoader::GameLoader() {}


Game GameLoader::readData(){
    YAML::Node config = YAML::LoadFile("map.yaml");
    std::vector<std::vector<int>> map;
    Player player(PLAYER_ID, Vector(0, 0));
    YAML::Node matrix = config["map"];
    int length = config["length"].as<int>();
    int width = config["width"].as<int>();
    mapLoader(map, player, matrix);
    return Game (map, player);
}

void GameLoader::mapLoader(std::vector<std::vector<int>>& map, Player& player,
                                                         YAML::Node& matrix){
    for (std::size_t i = 0; i < matrix.size(); i++) {
        std::vector<int> row;
        for (std::size_t j = 0; j < matrix[i].size(); j++) {
            int elem = matrix[i][j].as<int>();
            if (elem == PLAYER_ID){
                Vector startingPoint(i * matrix.size(), j * matrix[i].size());
                player.move(startingPoint);
            } else if (elem == WALL) {
                row.push_back(elem);
            } else {
                row.push_back(0);
            }
        }
        map.push_back(row);
    }
}
