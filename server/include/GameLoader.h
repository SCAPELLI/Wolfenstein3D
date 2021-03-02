#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <yaml-cpp/yaml.h>
#include "server/Items/OpenableItem.h"
#include "server/Items/Rocket.h"
//#include "Game.h"
#include "Item.h"


/*Clase que se encarga de cargar los datos del juego, incluyendo objetos*/
class GameLoader{
    int uniqueId;
    YAML::Node sprites;
    YAML::Node idConfig;
    YAML::Node map;
public:
    GameLoader();
    Item* itemLoader(int& idItem);
    Item* weaponLoader(int& idItem);
    Item* weaponLoader(std::string& itemName);
    OpenableItem* setTexture(int& idItem);
    Item* itemLoader(std::string& idItem);
    Rocket* createRocket();
    ~GameLoader();
};
#endif