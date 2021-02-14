#include "Map.h"
#include <yaml-cpp/yaml.h>
#include "Player.h"
#include <random>
#include <vector>
#include <iostream>
#include "../common/CellMap.h"
#include "../common/Items/Wall.h"
#define PLAYER_ID 1
#define TILE 32
#include "GameLoader.h"
#include "../common/ServerEvents/SpawnEvent.h"
#include "../common/ServerEvents/CreateMapEvent.h"

Map::Map(){}

Map::Map(std::vector<Player>& players,
         std::vector<AbstractEvent*>& newEvents){
    std::vector<std::vector<CellMap>> map;
    YAML::Node config = YAML::LoadFile("map.yaml");
    YAML::Node matrixConfig = config["map"];
    int numOfPlayer = 0;
    height = matrixConfig.size() - 1;
    width = matrixConfig[0].size() - 1;
    auto event = new CreateMapEvent(width, height);
    newEvents.push_back(event);
    for (std::size_t i = 0; i < matrixConfig.size(); i++) {
        std::vector<CellMap> row;
        for (std::size_t j = 0; j < matrixConfig[i].size(); j++) {
            int elem = matrixConfig[i][j].as<int>();
            CellMap position = CellMap();
            setElemInPosition(numOfPlayer, i , j, position, players, elem,
                              newEvents);
            row.push_back(position);
        }
        map.push_back(row);
    }
    matrix = map;
}

void Map::setElemInPosition(int& numOfPlayer, int pos1, int pos2,
                            CellMap& tileMap, std::vector<Player>& players,
                            int elem, std::vector<AbstractEvent*>& newEvents){
    GameLoader yaml;
    if (elem == PLAYER_ID) {
        players[numOfPlayer].setPosition(Vector(pos2 * TILE, pos1 * TILE));
        auto event = new SpawnEvent(SpawnEventType, players[numOfPlayer].getId(),
                                    PLAYER_ID, pos2 * 32, pos1 * 32);
        newEvents.push_back(event);
        tileMap.addPlayer(players.at(numOfPlayer));
        numOfPlayer++;
    } if (elem > 1 && elem < 100){
        Item* item = yaml.itemLoader(elem);
        auto event = new SpawnEvent(SpawnEventType, item->getUniqueId(),
                                item->getId(), pos2 * 32, pos1 * 32);
        newEvents.push_back(event);
        tileMap.addItem(item);
        return;
    }
    else if (elem >= 100 && elem < 200) {
        OpenableItem* door = yaml.setTexture(elem);
        if (door == nullptr){
            tileMap.setSolid();
            ItemWall* wall = new ItemWall(elem, "wall", 0);
            auto event = new SpawnEvent(SpawnEventType, wall->getUniqueId(),
                                        wall->getId(), pos1, pos2);
            newEvents.push_back(event);

        }
        else{
            auto event = new SpawnEvent(SpawnEventType, door->getUniqueId(),
                                        door->getId(), pos1, pos2);
            newEvents.push_back(event);
            tileMap.addItem(door);
            doors.push_back(door);
        }
    }
}

bool Map::isADoor(Player& player, std::vector<AbstractEvent*>& newEvents){
    Vector& pos = player.getScaledPosition();
    if (matrix[pos.y + 1][pos.x].isOpenable(player, newEvents) ||
        matrix[pos.y - 1][pos.x].isOpenable(player, newEvents) ||
        matrix[pos.y][pos.x + 1].isOpenable(player, newEvents) ||
        matrix[pos.y][pos.x - 1].isOpenable(player, newEvents))
        return true;
    return false;
}

std::vector<std::vector<CellMap>>& Map::getMatrix() {
    return matrix;
}
void Map::removePlayer(Player& player){
    Vector positionPlayer = player.getScaledPosition();
    matrix[positionPlayer.y][positionPlayer.x].removePlayer(player);
}
void Map::addPlayer(Player& player){
    Vector posScaled = Vector((player.getScaledPosition()));
    matrix[posScaled.y][posScaled.x].addPlayer(player);
}
bool Map::isOkToMove(Vector& futurePos){
    return !matrix[futurePos.y][futurePos.x].isSolid() &&
            futurePos.y < width && futurePos.x < height &&  //borro mejor y que ni sean atributos?
            futurePos.y > 0 && futurePos.x > 0 &&
            matrix[futurePos.y][futurePos.x].isOpen();
}

void Map::dropAllItems(Player& player){ //deberia llamar a newEvents
    Vector positionPlayer = player.getScaledPosition();
    matrix[positionPlayer.y][positionPlayer.x].dropItems(player);
}

void Map::dropItemPlayer(Player& player, Item itemPlayer){
    Vector positionPlayer = player.getScaledPosition();
    matrix[positionPlayer.y][positionPlayer.x].dropItemPlayer(&itemPlayer);
}

 void Map::changePosition(Vector& newPos, Player& player,
                              std::vector<AbstractEvent*>& newEvents){
     Vector positionPlayer = player.getScaledPosition();
     matrix[positionPlayer.y][positionPlayer.x].removePlayer(player); // ponerla como atributo!!
     matrix[newPos.y][newPos.x].addPlayer(player);
     matrix[newPos.y][newPos.x].getItemsTile(player, newEvents);
}

void Map::increaseCooldown() {
    for (std::size_t i = 0; i < doors.size(); i++) {
        doors[i]->incrementCooldown();
    }
}