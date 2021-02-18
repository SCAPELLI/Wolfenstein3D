#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <yaml-cpp/yaml.h>
#include <Items/OpenableItem.h>
//#include "Game.h"
#include "../common/Item.h"



class GameLoader{
    int uniqueId;
    YAML::Node sprites;
    YAML::Node idConfig;
    YAML::Node map;
public:
    GameLoader();
    void readData(int& speed);
    Item* itemLoader(int& idItem);
    void configWeapon(std::string& name, int& effect, int& minBullets, double& speed);
    OpenableItem* setTexture(int& idItem);
    Item* itemLoader(std::string& idItem);
    ~GameLoader();
};
#endif