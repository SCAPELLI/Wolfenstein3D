

#include "Player.h"
#include "GameLoader.h"
#include <vector>
#include <iostream>
#include <string>
#include "Exception.h"
#include "../common/Items/LockedDoor.h"
#include "../common/Items/OpenableItem.h"
#include "../common/Items/AmmoItem.h"
#include "../common/Items/Wall.h"
#define PLAYER_ID 1

GameLoader::GameLoader(){
    sprites = YAML::LoadFile("../Editor/sprites/sprites.yaml");
    idConfig = YAML::LoadFile("config.yaml");
    map = YAML::LoadFile("map.yaml");

}


void GameLoader::configWeapon(std::string& name, int& effect, int& minBullets,
                                                        double& speed){
    int cont = 0;
    for (YAML::const_iterator it=idConfig["Weapons"].begin();
                                it!=idConfig["Weapons"].end(); ++it){
        if (it->first.as<std::string>() == name){
            YAML::Node data = idConfig["Weapons"][it->first.as<std::string>()];
            effect = data["damage"].as<int>();
            minBullets = data["minBullets"].as<int>();
            speed = data["speed"].as<double>();
            return;
        }
        cont++;
    }
}

void GameLoader::readData(int& speed){
    YAML::Node matrix = map["map"];
    speed = map["speed"].as<int>();
    //int width = fileNode["width"].as<int>();
    //mapLoader(map, players, matrix);
}


Item* GameLoader::itemLoader(int& idItem) {
    std::string elem = sprites["items"][idItem]["type"].as<std::string>();
    int value = sprites["items"][idItem]["value"].as<int>();
    if (elem == "food" || elem == "med kit" ||
        elem == "blood") {
        return  new LifeGainItem(idItem, elem, value);
    }
    if (elem == "cross" || elem == "crown" ||
        elem == "chest"  || elem == "chalice") {
        return new PointGainItem(idItem, elem, value);
    }
    if (elem == "machine gun" || elem == "chain gun" ||
        elem == "rocket launcher" || elem == "pistol") {
        return new Weapon(idItem, elem);
    }
    if (elem == "ammo") {
        return new AmmoItem(idItem, elem, value);
    } if (elem == "key") {
        return new KeyItem(idItem, elem, value);
    }
    throw Exception("No se encontró ese ID en el archivo yaml");
}

void GameLoader::configItem(int& id, std::string&  itemName, int& effect){
    for (YAML::const_iterator it = sprites["items"].begin();
         it != sprites["items"].end(); ++it) {
        std::string type = sprites["items"][it->first.as<int>()]
        ["type"].as<std::string>(); // esto me da el nombre del item
        if (type == itemName) {
            int value = sprites["items"][it->first.as<int>()]["value"].as<int>();
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

Item* GameLoader::itemLoader(std::string& itemName) {
    for (YAML::const_iterator it = sprites["items"].begin();
                                 it != sprites["items"].end(); ++it) {
            std::string type = sprites["items"][ it->first.as<int>()]["type"].as<std::string>();
            if (itemName == type){
                int value = sprites["items"][it->first.as<int>()]["value"].as<int>();
                if (itemName == "food" || itemName == "med kit" || itemName == "blood") {
                    return  new LifeGainItem(it->first.as<int>(), itemName, value);
                }
                if (itemName == "cross" || itemName == "crown" ||
                    itemName == "chest" || itemName == "chalice") {
                    return new PointGainItem(it->first.as<int>(), itemName, value);
                }
                if (itemName == "machine gun" || itemName == "chain gun" ||
                    itemName == "rocket launcher" || itemName == "pistol") {
                    return new Weapon(it->first.as<int>(), type);
                }
                if (itemName == "ammo") {
                    return new AmmoItem(it->first.as<int>(), itemName, value);
                } if (itemName == "key") {
                    return new KeyItem(it->first.as<int>(), itemName, value);
                }
            }
        }
    throw Exception("No se encontró ese ID en el archivo yaml");
}

OpenableItem* GameLoader::setTexture(int& idItem) {
    for (YAML::const_iterator it = sprites["textures"].begin();
                         it != sprites["textures"].end(); ++it) {
        if (it->first.as<int>() == idItem) {
            std::string elem = sprites["textures"][idItem].as<std::string>();
            if (elem =="false wall" || elem == "secret passage"){
                return  new OpenableItem(idItem, elem, 0);
            }
            else if (elem == "door"){
                return new OpenableItem(idItem, elem, 0);
            }
            else if (elem == "locked door"){
                return new LockedDoor(idItem, elem, 0);
            }
            else{
                break;
            }
        }
    }
    return nullptr;
}


GameLoader::~GameLoader(){}