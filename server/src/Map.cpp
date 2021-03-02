#include "server/include/Map.h"
#include <yaml-cpp/yaml.h>
#include "server/include/Player.h"
#include <vector>
#include "server/include/CellMap.h"
#include "common/ServerEvents/SpawnEvent.h"
#include "common/ServerEvents/CreateMapEvent.h"
#include "common/ServerEvents/SpawnNotMovableEvent.h"
#include "common/ServerEvents/DespawnEvent.h"
#include "common/ServerEvents/DoorOpenedEvent.h"
#include <bits/stdc++.h>
#define DOORTOCHANGE 161

Map::Map(){}

Map::Map(std::vector<Player>& players,
         std::vector<AbstractEvent*>& newEvents, int levelId): factory(){
    std::string pathLevel = "../../server/maps/" + std::to_string(levelId)+ ".yaml";
    YAML::Node config = YAML::LoadFile(pathLevel);
    std::vector<std::vector<int>> map = config["map"].as<std::vector<std::vector<int>>>();
    int numOfPlayer = 0;
    height = map.size() - 1;
    width = map[0].size() - 1;
    for (std::size_t i = 0; i < map.size(); i++) {
        std::vector<CellMap> row;
        for (std::size_t j = 0; j < map[i].size(); j++) {
            int elem = map[i][j];
            CellMap position = CellMap();
            setElemInPosition(numOfPlayer, i , j, position, players, elem,
                              newEvents);
            row.push_back(position);
        }
        matrix.push_back(row);
    }
}

void Map::setElemInPosition(int& numOfPlayer, int pos1, int pos2,
                            CellMap& tileMap, std::vector<Player>& players,
                            int elem, std::vector<AbstractEvent*>& newEvents){
    if (elem == PLAYER_ID and (numOfPlayer+1)<=players.size()) {
        players[numOfPlayer].setPosition(Vector(pos2 * TILE, pos1 * TILE));
        tileMap.addPlayer(players.at(numOfPlayer));
        numOfPlayer++;
    } if (elem > 1 && elem < 50){
        insertItem(elem, pos1, pos2, tileMap, newEvents);
    }
    else if (elem >= 50 && elem < 100){
        insertWeapon(elem, pos1, pos2, tileMap, newEvents);
    }
    else if (elem >= 100 && elem < 300) {
        OpenableItem* door = factory.setTexture(elem);
        if (door == nullptr){
            tileMap.setSolid();
            auto event = new SpawnNotMovableEvent(SpawnNotMovableType, elem, pos1, pos2);
            newEvents.push_back(event);
            return;
        }
        insertDoor(elem,door, pos1, pos2,tileMap, newEvents);
    }
}

void Map::insertItem(int& elem, int& pos1, int& pos2,
                     CellMap& tile, std::vector<AbstractEvent*>& newEvents){
    Item* item = factory.itemLoader(elem);
    auto event = new SpawnEvent(SpawnEventType, item->getUniqueId(),
                                item->getId(), pos1 * TILE, pos2 * TILE);
    newEvents.push_back(event);
    tile.addItem(item);
}

void Map::insertWeapon(int& elem, int& pos1, int& pos2,
                     CellMap& tile, std::vector<AbstractEvent*>& newEvents){
    Item* item = factory.weaponLoader(elem);
    auto event = new SpawnEvent(SpawnEventType, item->getUniqueId(),
                                item->getId() + WEAPONSGAP, pos1 * TILE, pos2 * TILE);
    newEvents.push_back(event);
    tile.addItem(item);
}
void Map::insertDoor(int& elem, OpenableItem* door, int& pos1, int& pos2,
                     CellMap& tile, std::vector<AbstractEvent*>& newEvents){
    auto event = new SpawnEvent(SpawnEventType, door->getUniqueId(), door->getId(), pos2, pos1);
    newEvents.push_back(event);
    tile.addItem(door);
    doors.push_back(door);
}

void Map::launchRocket(Player& player, Vector& direction,
                                    std::vector<AbstractEvent*>& newEvents) {
    return;
    Rocket* rocket =  factory.createRocket();
    player.setRocket(direction, rocket);
    rocket->sender = player.getId();
    rockets.push_back(rocket);

}
bool Map::collide(Rocket* rocket, std::vector<AbstractEvent*>& newEvents) {
    Vector currentPos = rocket->currentPosition;
    if (matrix[currentPos.y][currentPos.x].impacts(rocket)) {
        rocket->impactPoint = Vector(currentPos.x, currentPos.y);
        newEvents.push_back(new DespawnEvent(DespawnEventType,
                                             rocket->getUniqueId(),
                                             rocket->getId()));
        explodeAdyacents(rocket);
        return true;
    }
    return false;
}
void Map::explodeAdyacents(Rocket* rocket){
    Vector impact = rocket->impactPoint;
    if ((impact.y + 1) < width && (impact.y + 1) > 0)
        matrix[impact.y + 1][impact.x].explode(rocket);
    if ((impact.y - 1) < width && (impact.y - 1) > 0)
        matrix[impact.y - 1][impact.x].explode(rocket);
    if ((impact.x + 1) < height && (impact.x + 1) > 0)
        matrix[impact.y][impact.x + 1].explode(rocket);
    if ((impact.x - 1) < height && (impact.y - 1) > 0)
        matrix[impact.y][impact.x - 1].explode(rocket);

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
        if (changeBecauseLockedDoor(doorPos, newEvents))
            matrix[doorPos.x][doorPos.y].isOpenable(player, newEvents);
        return true;
    }

    return false;
}
bool Map::changeBecauseLockedDoor(Vector& doorPos, std::vector<AbstractEvent*>& newEvents){
    if (!matrix[doorPos.x][doorPos.y].isLockedDoor()) return false;
    int idDoor = DOORTOCHANGE;
    OpenableItem* newDoor = factory.setTexture(idDoor);
    OpenableItem* currentDoor = matrix[doorPos.y][doorPos.x].getDoor();
    newEvents.push_back(new DespawnEvent(DespawnEventType,
                                         currentDoor->getUniqueId(),
                                         currentDoor->getId()));
    matrix[doorPos.x][doorPos.y].addItem(newDoor);
    auto it = std::find(doors.begin(), doors.end(), currentDoor);
    if (it != doors.end()){
        (*it) = newDoor;
    }
    delete(currentDoor);
    newEvents.push_back(new SpawnEvent(SpawnEventType,
                                       newDoor->getUniqueId(), newDoor->getId(),
                                       doorPos.x, doorPos.y));
    return true;
}
bool Map::isOkToMove(Vector& futurePos){
    return !matrix[futurePos.y][futurePos.x].isSolid() &&
            futurePos.x < width && futurePos.y < height &&
            futurePos.y > 0 && futurePos.x > 0 &&
            matrix[futurePos.y][futurePos.x].isOpen();
}

void Map::dropAllItems(Player& player, std::vector<AbstractEvent*>& newEvents){
    Vector positionPlayer = player.getScaledPosition();
    matrix[positionPlayer.y][positionPlayer.x].dropItems(player, factory, newEvents);
}

 void Map::changePosition(Vector& newPos, Player& player,
                              std::vector<AbstractEvent*>& newEvents){
     Vector positionPlayer = player.getScaledPosition();
     matrix[positionPlayer.y][positionPlayer.x].removePlayer(player);
     matrix[newPos.y][newPos.x].addPlayer(player);
     matrix[newPos.y][newPos.x].getItemsTile(player, newEvents);
}

int Map::increaseCooldown(std::vector<AbstractEvent*>& newEvents) {
    for (std::size_t i = 0; i < doors.size(); i++) {
        doors[i]->incrementCooldown();
    }
    int idPlayer = -1;
    auto it = rockets.begin();
    while (it != rockets.end()) {
        Vector posRocket = (*it)->currentPosition;
        if ( posRocket.y < width && posRocket.x < height &&
            !matrix[posRocket.y][posRocket.x].isSolid()) {
            (*it)->incrementCooldown(newEvents);
            if (collide((*it), newEvents)) {
                idPlayer = (*it)->sender;
                delete (*it);
            }else{
              ++it;
            }
        }
    }
    return idPlayer;
}


double Map::getWidth() {
    return width;
}
double Map::getHeight() {
    return height;
}
