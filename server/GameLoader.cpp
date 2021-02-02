

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
                            KeyItem& keys, AmmoItem& bullets, bool dead){ // pasar esta cosa al constructor directamente
    YAML::Node fileNode = YAML::LoadFile("config.yaml");
    GameLoader yamlItems;
    if (!dead)
        lifes = fileNode["Player"]["lifes"].as<int>();
    health = fileNode["Player"]["health"].as<int>();
    radius = fileNode["Player"]["radius"].as<int>();
    bullets = AmmoItem(3, "ammo", fileNode["Player"]["bullets"].as<int>());
    points = PointGainItem();
    angle = fileNode["Player"]["angle"].as<double>();
    int cont = 0;
    for (YAML::const_iterator it=fileNode["Weapons"].begin();
                                        it!=fileNode["Weapons"].end(); ++it){
        std::string weaponType = it->first.as<std::string>();
        if(weaponType =="knife" || weaponType == "pistol"){
            YAML::Node data = fileNode["Weapons"][it->first.as<std::string>()];
            bag.insert(std::make_pair(cont,
                    Weapon(cont, weaponType, data["damage"].as<int>(),
                    data["minBullets"].as<int>(),
                    data["speed"].as<double>())));
            idWeapon = cont;
        }
        cont++;
    }
}

void GameLoader::configWeapon(std::string& name, int& effect, int& minBullets,
                                                        double& speed){
    int cont = 0;
    YAML::Node config = YAML::LoadFile("config.yaml");
    std::cout << config["Weapons"] << "\n";
    for (YAML::const_iterator it=config["Weapons"].begin();
                                it!=config["Weapons"].end(); ++it){
        if (it->first.as<std::string>() == name){
            YAML::Node data = config["Weapons"][it->first.as<std::string>()];
            effect = data["damage"].as<int>();
            minBullets = data["minBullets"].as<int>();
            speed = data["speed"].as<double>();
            return;
        }
        cont++;
    }
}

void GameLoader::readData(int& speed){
    YAML::Node config = YAML::LoadFile("map.yaml");
    YAML::Node matrix = config["map"];
    speed = config["speed"].as<int>();
    //int width = fileNode["width"].as<int>();
    //mapLoader(map, players, matrix);
}

Item* GameLoader::itemLoader(int& idItem) {
    YAML::Node fileNode = YAML::LoadFile("../Editor/sprites/sprites.yaml");
    std::string elem = fileNode["items"][idItem]["type"].as<std::string>();
    int value = fileNode["items"][idItem]["value"].as<int>();
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



Item* GameLoader::itemLoader(std::string& itemName) {
    YAML::Node fileNode = YAML::LoadFile("../Editor/sprites/sprites.yaml");
    for (YAML::const_iterator it = fileNode["items"].begin();
                                 it != fileNode["items"].end(); ++it) {
            std::string type = fileNode["items"][ it->first.as<int>()]["type"].as<std::string>();
            if (itemName == type){
                int value = fileNode["items"][it->first.as<int>()]["value"].as<int>();
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

void GameLoader::setTexture(int& idItem, CellMap& tileMap) {
    YAML::Node fileNode = YAML::LoadFile("../Editor/sprites/sprites.yaml");
    for (YAML::const_iterator it = fileNode["textures"].begin();
                         it != fileNode["textures"].end(); ++it) {
        if (it->first.as<int>() == idItem) {
            std::string elem = fileNode["textures"][idItem].as<std::string>();
            if (elem =="false wall"){
                tileMap.addItem(new OpenableItem(idItem, elem, -1));
            }
            else if (elem == "door"){
                tileMap.addItem(new OpenableItem(idItem, elem, 0));
            }
            else if (elem == "locked door"){
                tileMap.addItem(new LockedDoor(idItem, elem, -1));
            }
            else{
                tileMap.setSolid();
            }
        }
    }
}


GameLoader::~GameLoader(){}