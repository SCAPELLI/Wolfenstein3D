

#include "Player.h"
#include "GameLoader.h"
#include <vector>
#include <iostream>
#include <string>
#include "Exception.h"
#include "../common/Items/LockedDoor.h"
#include "../common/Items/OpenableItem.h"
#include "../common/Items/AmmoItem.h"
#define PLAYER_ID 1

GameLoader::GameLoader(){}

void GameLoader::configPlayer(int& lifes, int& health, int& radius,
                            double& angle, std::map<int, Weapon>& bag,
                            int& idWeapon, PointGainItem& points,
                            KeyItem& keys, AmmoItem& bullets){
    YAML::Node fileNode = YAML::LoadFile("config.yaml");
    GameLoader yamlItems;
    lifes = fileNode["Player"]["lifes"].as<int>();
    health = fileNode["Player"]["health"].as<int>();
    radius = fileNode["Player"]["radius"].as<int>();
    bullets = AmmoItem();
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

Item GameLoader::itemLoader(int& idItem) {
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
        return AmmoItem(idItem, elem, value);
    } if (elem.compare("key")) {
        return KeyItem(idItem, elem, value);
    }
    throw Exception("No se encontró ese ID en el archivo yaml");
}

void GameLoader::configItem(int& id, std::string&  itemName, int& effect){
    YAML::Node fileNode = YAML::LoadFile("../Editor/sprites/sprites.yaml");
    for (YAML::const_iterator it = fileNode["items"].begin();
                             it != fileNode["items"].end(); ++it) {
        std::string type = fileNode["items"][it->first.as<int>()]
                                        ["type"].as<std::string>(); // esto me da el nombre del item
        if (type == itemName) {
            int value = fileNode["items"][it->first.as<int>()]["value"].as<int>();
            if (type == "food" || type == "med kit" || type == "blood") {
                id = it->first.as<int>();
                effect = value;
                return;
            }
            if (type == "cross" || type == "crown" || type == "chest" ||
                                                            type == "chalice") {
                id = it->first.as<int>();
                effect = value;
                return;
            }
            if (type == "ammo") {
                id = it->first.as<int>();
                effect = value;
                return;
            }
            if (type == "key") {
                id = it->first.as<int>();
                effect = value;
                return;
            }
        }
    }
    throw Exception("No se encontró ese ID en el archivo yaml");
}



Item GameLoader::itemLoader(std::string& itemName) {
    YAML::Node fileNode = YAML::LoadFile("../Editor/sprites/sprites.yaml");
    for (YAML::const_iterator it = fileNode["items"].begin();
                                 it != fileNode["items"].end(); ++it) {
            std::string type = fileNode["items"][ it->first.as<int>()]["type"].as<std::string>();
            if (itemName == type){
                int value = fileNode["items"][it->first.as<int>()]["value"].as<int>();
                if (itemName == "food" || itemName == "med kit" || itemName == "blood") {
                    return  LifeGainItem(it->first.as<int>(), itemName, value);
                }
                if (itemName == "cross" || itemName == "crown" ||
                    itemName == "chest" || itemName == "chalice") {
                    return  PointGainItem(it->first.as<int>(), itemName, value);
                }
                if (itemName == "machine gun" || itemName == "chain gun" ||
                    itemName == "rocket launcher" || itemName == "pistol") {
                    return Weapon(it->first.as<int>());
                }
                if (itemName == "ammo") {
                    return AmmoItem(it->first.as<int>(), itemName, value);
                } if (itemName == "key") {
                    return KeyItem(it->first.as<int>(), itemName, value);
                }
            }
        }
    throw Exception("No se encontró ese ID en el archivo yaml");
}

void GameLoader::setTexture(int& idItem, CellMap& tileMap) {
    YAML::Node fileNode = YAML::LoadFile("../Editor/sprites/sprites.yaml");
    for (YAML::const_iterator it = fileNode["textures"].begin();
                         it != fileNode["textures"].end(); ++it) {
        if (it->first.as<int>() == idItem) {
            std::string elem = fileNode["textures"][idItem].as<std::string>();
            if (elem.compare("false wall")){
                tileMap.addItem(OpenableItem(idItem, elem, -1));
            }
            else if (elem.compare("door")){
                tileMap.addItem(OpenableItem(idItem, elem, 0));
            }
            else if (elem.compare("locked door")){
                tileMap.addItem(LockedDoor(idItem, elem, -1));
            }
            return;
        }
    }
    tileMap.setSolid();
}


GameLoader::~GameLoader(){}