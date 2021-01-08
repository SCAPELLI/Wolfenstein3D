

#include "Player.h"
#include "GameLoader.h"
#include <vector>
#include <iostream>
#include <string>
#define WALL 2
#define PLAYER_ID 1
#define TILE 32
#define BULLET_ID 100

GameLoader::GameLoader() {}

void GameLoader::configPlayer(int& lifes, int& health, int& radius,
                            double& angle, std::map<int, Weapon>& bag,
                            int& idWeapon, Item& bullets){
    YAML::Node config = YAML::LoadFile("config.yaml");
    lifes = config["Player"]["lifes"].as<int>();
    health = config["Player"]["health"].as<int>();
    radius = config["Player"]["radius"].as<int>();
    bullets = Item(BULLET_ID, config["Player"]["bullets"].as<int>());
    angle = config["Player"]["angle"].as<double>();
    int cont = 0;
    for (YAML::const_iterator it=config["Weapons"].begin();
                                        it!=config["Weapons"].end(); ++it){
        if(it->first.as<std::string>().compare("Knife") == 0 ||
                it->first.as<std::string>().compare("Gun") == 0){
            YAML::Node data = config["Weapons"][it->first.as<std::string>()];
            bag.insert(std::make_pair(cont,
                    Weapon(cont,data["damage"].as<int>(),
                    data["minBullets"].as<int>(),
                    data["speed"].as<double>())));
            idWeapon = cont;
        }
        cont++;
    }
}

void GameLoader::readData( int& speed){
    YAML::Node config = YAML::LoadFile("map.yaml");
    YAML::Node matrix = config["map"];
    speed = config["speed"].as<int>();
    //int width = config["width"].as<int>();
    //mapLoader(map, players, matrix);
}

//void GameLoader::mapLoader(Map& map,
//                           std::vector<Player>& players, YAML::Node& matrix){
//    int numOfPlayer = 0;
//    for (std::size_t i = 0; i < matrix.size(); i++) {
//        std::vector<int> row;
//        for (std::size_t j = 0; j < matrix[i].size(); j++) {
//            int elem = matrix[i][j].as<int>();
//            if (elem == PLAYER_ID){
//                players.emplace_back(Player(numOfPlayer,
//                                            Vector (i * TILE, j * TILE)));
//                numOfPlayer++;
//                row.push_back(0);
//            } else if (elem) {
//                row.push_back(WALL);
//            } else {
//                row.push_back(0);
//            }
//        }
//        map.push_back(row);
//    }
//}

GameLoader::~GameLoader(){}