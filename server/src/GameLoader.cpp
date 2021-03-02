

#include "server/include/Player.h"
#include "server/include/GameLoader.h"
#include <vector>
#include <iostream>
#include <string>
#include "common/include/Exception.h"
#include "server/Items/LockedDoor.h"


GameLoader::GameLoader() : uniqueId(1){
    sprites = YAML::LoadFile("../../Editor/sprites/sprites.yaml");
    idConfig = YAML::LoadFile("../../server/config/config.yaml");
    map = YAML::LoadFile("../../server/maps/1.yaml");
}

Item* GameLoader::itemLoader(int& idItem) {
    std::string elem = sprites["items"][idItem]["type"].as<std::string>();
    int value = sprites["items"][idItem]["value"].as<int>();
    if (elem == "food" || elem == "med kit" ||
        elem == "blood") {
        Item* item = new LifeGainItem(idItem, elem, value, uniqueId);
        uniqueId++;
        return item;
    }
    if (elem == "cross" || elem == "crown" ||
        elem == "chest"  || elem == "chalice") {
        Item* item = new PointGainItem(idItem, elem, value, uniqueId);
        uniqueId++;
        return item;
    }
    if (elem == "ammo") {
        Item* item = new AmmoItem(idItem, elem, value, uniqueId);
        uniqueId++;
        return item;
    }
    if (elem == "key") {
        Item* item = new KeyItem(idItem, elem, value, uniqueId);
        uniqueId++;
        return item;
    }
    throw Exception("No se encontró ese ID en el archivo yaml");
}

Item* GameLoader::weaponLoader(int& idItem){
    std::string elem = sprites["weapons"][idItem]["type"].as<std::string>();
    if (elem == "machine gun" || elem == "chain gun" ||
        elem == "rocket launcher" || elem == "pistol") {
        YAML::Node data = idConfig["Weapons"][elem];
        Item* item = new Weapon(idItem - WEAPONSGAP, elem, uniqueId, data["damage"].as<int>(),
                                data["minBullets"].as<int>(), data["cooldownTimer"].as<int>());
        uniqueId++;
        return item;
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
                    Item* item = new LifeGainItem(it->first.as<int>(), itemName, value, uniqueId);
                    uniqueId++;
                    return item;
                }
                if (itemName == "cross" || itemName == "crown" ||
                    itemName == "chest" || itemName == "chalice") {
                    Item* item = new PointGainItem(it->first.as<int>(), itemName, value, uniqueId);
                    uniqueId++;
                    return item;
                }
                 if (itemName == "ammo") {
                    Item* item = new AmmoItem(it->first.as<int>(), itemName, value, uniqueId);
                    uniqueId++;
                    return item;
                } if (itemName == "key") {
                    Item* item = new KeyItem(it->first.as<int>(), itemName, value, uniqueId);
                    uniqueId++;
                    return item;
                }
            }

        }
    throw Exception("No se encontró ese ID en el archivo yaml");
}

Item* GameLoader::weaponLoader(std::string &itemName) {
    for (YAML::const_iterator it = sprites["weapons"].begin();
         it != sprites["weapons"].end(); ++it) {
        if (itemName == "machine gun" || itemName == "chain gun" ||
            itemName == "rocket launcher" || itemName == "pistol") {
            YAML::Node data = idConfig["Weapons"][itemName];
            Item *item = new Weapon(it->first.as<int>() - WEAPONSGAP,
                                     itemName, uniqueId, data["damage"].as<int>(),
                        data["minBullets"].as<int>(), data["cooldownTimer"].as<int>());
            uniqueId++;
            return item;
        }
    }
    return nullptr;
}
OpenableItem* GameLoader::setTexture(int& idItem) {
    for (YAML::const_iterator it = sprites["textures"].begin();
                         it != sprites["textures"].end(); ++it) {
        if (it->first.as<int>() == idItem) {
            std::string elem = sprites["textures"][idItem].as<std::string>();
            if (elem =="false wall" || elem == "secret passage"){
                OpenableItem* item = new OpenableItem(idItem, elem, 0, uniqueId);
                uniqueId++;
                return item;
            }
            else if (elem == "door"){
                OpenableItem* item = new OpenableItem(idItem, elem, 0, uniqueId);
                uniqueId++;
                return item;
            }
            else if (elem == "locked door"){
                OpenableItem* item = new LockedDoor(idItem, elem, 0, uniqueId);
                uniqueId++;
                return item;
            }
            else{
                break;
            }
        }
    }
    return nullptr;
}


GameLoader::~GameLoader(){}