

#include "Player.h"
#include "GameLoader.h"
#include <vector>
#include <iostream>
#include <string>
#include "Exception.h"
#include "../common/Items/LockedDoor.h"
#include "../common/Items/OpenableItem.h"
#define PLAYER_ID 1
#define BULLET_ID 100

GameLoader::GameLoader(){}

void GameLoader::configPlayer(int& lifes, int& health, int& radius,
                            double& angle, std::map<int, Weapon>& bag,
                            int& idWeapon,
                            Item& bullets,PointGainItem points, KeyItem keys){
    YAML::Node fileNode = YAML::LoadFile("config.yaml");
    GameLoader yamlItems;
    lifes = fileNode["Player"]["lifes"].as<int>();
    health = fileNode["Player"]["health"].as<int>();
    radius = fileNode["Player"]["radius"].as<int>();
    bullets = Item(BULLET_ID, "ammo", fileNode["Player"]["bullets"].as<int>());
    angle = fileNode["Player"]["angle"].as<double>();
    int cont = 0;
    for (YAML::const_iterator it=fileNode["Weapons"].begin();
                                        it!=fileNode["Weapons"].end(); ++it){
        if(it->first.as<std::string>().compare("Knife") == 0 ||
                it->first.as<std::string>().compare("Gun") == 0){
            YAML::Node data = fileNode["Weapons"][it->first.as<std::string>()];
            bag.insert(std::make_pair(cont,
                    Weapon(cont,data["damage"].as<int>(),
                    data["minBullets"].as<int>(),
                    data["speed"].as<double>())));
            idWeapon = cont;
        }
        cont++;
    }
}

void GameLoader::configWeapon(int& id,int& effect, int& minBullets, double& speed){
    int cont = 0;
    YAML::Node config = YAML::LoadFile("config.yaml");
    for (YAML::const_iterator it=config["Weapons"].begin();
                                it!=config["Weapons"].end(); ++it){
        if (cont == id){
            YAML::Node data = config["Weapons"];
            effect = data["damage"].as<int>();
            minBullets = data["minBullets"].as<int>();
            speed = data["speed"].as<double>();
        }
    }
}

void GameLoader::readData( int& speed){
    YAML::Node config = YAML::LoadFile("map.yaml");
    YAML::Node matrix = config["map"];
    speed = config["speed"].as<int>();
    //int width = fileNode["width"].as<int>();
    //mapLoader(map, players, matrix);
}

Item GameLoader::itemLoader(int idItem) {
    YAML::Node fileNode = YAML::LoadFile("../Editor/sprites/sprites.yaml");
    std::string elem = fileNode["items"][idItem]["type"].as<std::string>();
    int value = fileNode["items"][idItem]["value"].as<int>();
    if (elem.compare("food") || elem.compare("med kit") ||
        elem.compare("blood")) {
        return  LifeGainItem(idItem, elem, value);
    }
    if (elem.compare("cross") || elem.compare("crown") ||
        elem.compare("chest") || elem.compare("chalice")) {
        return  PointGainItem(idItem, elem, value);
    }
    if (elem.compare("machine gun") || elem.compare("chain gun") ||
        elem.compare("rocket launcher") || elem.compare("pistol")) {
        return Weapon(idItem);
    }
    if (elem.compare("ammo")) {
        return Item(idItem, elem, value);
    } if (elem.compare("key")) {
        return KeyItem(idItem, elem, value);
    }
    throw Exception("No se encontró ese ID en el archivo yaml");
}

Item GameLoader::itemLoader(std::string idItem) {
    fileNode = YAML::LoadFile("../Editor/sprites/sprites.yaml");
    for (YAML::const_iterator it = fileNode["items"].begin();
                             it != fileNode["items"].end(); ++it) {
            std::string type = it->first["type"].as<std::string>();
            std::string elem = fileNode["items"][it->first.as<int>()]
                                           ["type"].as<std::string>();
            int value = fileNode["items"][it->first]["value"].as<int>();
            if (idItem == "food" || idItem == "med kit" || idItem == "blood") {
                return  LifeGainItem(it->first.as<int>(), idItem, value);
            }
            if (idItem == "cross" || idItem == "crown" ||
                idItem == "chest" || idItem == "chalice") {
                return  PointGainItem(it->first.as<int>(), idItem, value);
            }
            if (idItem == "machine gun" || idItem == "chain gun" ||
                idItem == "rocket launcher" || idItem == "pistol") {
                return Weapon(it->first.as<int>());
            }
            if (idItem == "ammo") {
                return Item(it->first.as<int>(), idItem, value);
            } if (elem.compare("key")) {
                return KeyItem(it->first.as<int>(), idItem, value);
            }
        }
    throw Exception("No se encontró ese ID en el archivo yaml");
}

void GameLoader::setTexture(int idItem, CellMap& tileMap) {
    fileNode = YAML::LoadFile("../Editor/sprites/sprites.yaml");
    for (YAML::const_iterator it = fileNode["textures"].begin();
                         it != fileNode["textures"].end(); ++it) {
        if (it->first.as<int>() == idItem) {
            std::string elem = fileNode["textures"][idItem].as<std::string>();
            if (elem.compare("false wall")){
                tileMap.addItem(OpenableItem(idItem, elem, -1));
            }
            if (elem.compare("door")){
                tileMap.addItem(OpenableItem(idItem, elem, 0));
            }
            if (elem.compare("locked door")){
                tileMap.addItem(LockedDoor(idItem, elem, -1));
            }
            return;
        }
    }
    tileMap.setSolid();
}


GameLoader::~GameLoader(){}