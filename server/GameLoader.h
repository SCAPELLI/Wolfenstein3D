#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <yaml-cpp/yaml.h>
#include <Items/OpenableItem.h>
//#include "Game.h"
#include "Item.h"



class GameLoader{
    int uniqueId;
    YAML::Node sprites;
    YAML::Node idConfig;
    YAML::Node map;
public:
    GameLoader();
    void readData(int& speed);
    Item* itemLoader(int& idItem);
    int assignUniqueId();
    Item* weaponLoader(int& idItem);
    Item* weaponLoader(std::string& itemName);
    OpenableItem* setTexture(int& idItem);
    Item* itemLoader(std::string& idItem);
    ~GameLoader();
};
#endif