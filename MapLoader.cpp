
#include <yaml-cpp/yaml.h>
#include "Player.h"
#include <random>
#include "Map.h"
#include "MapLoader.h"
#include <vector>
#include <iostream>
#define WALL 2
#define PLAYER_ID 1

MapLoader::MapLoader() {}



void MapLoader::readYaml(){
    YAML::Node config = YAML::LoadFile("map.yaml");
    std::vector<int> map;
    Player player(PLAYER_ID, Vector(0, 0));
    YAML::Node matrix = config["map"];
    int length = config["length"].as<int>();
    int width = config["width"].as<int>();
    for (std::size_t i = 0; i < matrix.size(); i++) {
        for (std::size_t j = 0; j < matrix[i].size(); j++) {
            int elem = matrix[i][j].as<int>();
            if (elem == PLAYER_ID){
                Vector startingPoint(i * width, j * length);
                 player.move(startingPoint);
            } else if (elem == WALL) {
                map.push_back(elem);
            } else {
                map.push_back(0);
            }
        }
    }
    Map game(map, player);
}


