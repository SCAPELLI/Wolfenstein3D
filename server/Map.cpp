#include "Map.h"
#include <yaml-cpp/yaml.h>
#include "Player.h"
#include <random>
#include <vector>
#include <iostream>
#include "CellMap.h"
#include "Constants.h"
#include "GameLoader.h"
#include "../common/ServerEvents/SpawnEvent.h"
#include "../common/ServerEvents/CreateMapEvent.h"
#include "../common/ServerEvents/SpawnNotMovableEvent.h"
#include "ServerEvents/DoorOpenedEvent.h"

Map::Map(){}

Map::Map(std::vector<Player>& players,
         std::vector<AbstractEvent*>& newEvents): factory(){
    std::vector<std::vector<CellMap>> map;
    YAML::Node config = YAML::LoadFile("../server/maps/1.yaml");
    YAML::Node matrixConfig = config["map"];
    int numOfPlayer = 0;
    height = matrixConfig.size() - 1;
    width = matrixConfig[0].size() - 1;
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
    if (elem == PLAYER_ID) {
        players[numOfPlayer].setPosition(Vector(pos2 * TILE, pos1 * TILE));
        tileMap.addPlayer(players.at(numOfPlayer));
        numOfPlayer++;
    } if (elem > 1 && elem < 50){
        Item* item = factory.itemLoader(elem);
        auto event = new SpawnEvent(SpawnEventType, item->getUniqueId(),
                                item->getId(), pos1 * TILE, pos2 * TILE);
        newEvents.push_back(event);
        tileMap.addItem(item);
        return;
    }
    else if (elem >= 50 && elem < 100){
        Item* item = factory.weaponLoader(elem);
        auto event = new SpawnEvent(SpawnEventType, item->getUniqueId(),
                                    item->getId() + 49, pos1 * TILE, pos2 * TILE);
        newEvents.push_back(event);
        tileMap.addItem(item);
        return;
    }
    else if (elem >= 100 && elem < 300) {
        OpenableItem* door = factory.setTexture(elem);
        if (door == nullptr){
            tileMap.setSolid();
            auto event = new SpawnNotMovableEvent(SpawnNotMovableType, elem, pos1, pos2);
            newEvents.push_back(event);
        }
        else{
            auto event = new SpawnEvent(SpawnEventType, door->getUniqueId(), door->getId(), pos2, pos1);
            newEvents.push_back(event);
            tileMap.addItem(door);
            doors.push_back(door);
        }
    }
//    else if (elem >= 300 ){ // los que van a ser caminables
//        auto event = new SpawnNotMovableEvent(SpawnNotMovableType, elem, pos1, pos2);
//        newEvents.push_back(event);
//    }
}

void Map::launchRocket(Rocket* rocket, Vector& direction,
                                    std::vector<AbstractEvent*>& newEvents){
    Player* sender = rocket->sender;
    int impactPointX = sender->getScaledPosition().x;
    int impactPointY = sender->getScaledPosition().y;
    while (impactPointY < width && impactPointX < height &&
            !matrix[impactPointY][impactPointX].isSolid()) {
        if (matrix[impactPointY][impactPointX].impacts(rocket,newEvents))
            break;
        impactPointX += direction.x;
        impactPointY += direction.y;
    }
    rocket->impactPoint = Vector(impactPointX, impactPointY);
    if ((impactPointY +1) < width && (impactPointY +1) > 0)
        matrix[impactPointY + 1][impactPointX].explode(rocket, newEvents);
    if ((impactPointY -1) < width && (impactPointY -1) > 0)
        matrix[impactPointY - 1][impactPointX].explode(rocket, newEvents);
    if ((impactPointX +1) < height && (impactPointX +1) > 0)
        matrix[impactPointY][impactPointX + 1].explode(rocket, newEvents);
    if ((impactPointX -1) < height && (impactPointY -1) > 0)
        matrix[impactPointY][impactPointX - 1].explode(rocket, newEvents);
    delete(rocket);
}

bool Map::isADoor(Player& player, std::vector<AbstractEvent*>& newEvents){
    Vector& pos = player.getScaledPosition();
    Vector doorPos(-1, -1);
    if (pos.y +1 < width &&
        matrix[pos.y + 1][pos.x].isOpenable(player, newEvents))
        doorPos += Vector(pos.y + 2, pos.x + 1);
    if (pos.y -1 > 0 &&
            matrix[pos.y - 1][pos.x].isOpenable(player, newEvents))
        doorPos += Vector(pos.y, pos.x + 1);
    if (pos.x +1 < height &&
        matrix[pos.y][pos.x + 1].isOpenable(player, newEvents))
        doorPos += Vector(pos.y + 1, pos.x + 2);
    if (pos.y -1 > 0 &&
        matrix[pos.y][pos.x - 1].isOpenable(player, newEvents))
        doorPos += Vector(pos.y + 1, pos.x);

    if (doorPos.x != -1){
        newEvents.push_back(new DoorOpenedEvent(DoorOpenedEventType, doorPos.y, doorPos.x));
        return true;
    }

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
            futurePos.x < width && futurePos.y < height &&
            futurePos.y > 0 && futurePos.x > 0 &&
            matrix[futurePos.y][futurePos.x].isOpen();
}

void Map::dropAllItems(Player& player, std::vector<AbstractEvent*>& newEvents){ //deberia llamar a newEvents
    Vector positionPlayer = player.getScaledPosition();
    matrix[positionPlayer.y][positionPlayer.x].dropItems(player, factory, newEvents);
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

double Map::getWidth() {
    return width;
}
double Map::getHeight() {
    return height;
}
