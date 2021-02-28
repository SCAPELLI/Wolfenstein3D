#include "Map.h"
#include <yaml-cpp/yaml.h>
#include "Player.h"
#include <vector>
#include "CellMap.h"
#include "../common/ServerEvents/SpawnEvent.h"
#include "../common/ServerEvents/CreateMapEvent.h"
#include "../common/ServerEvents/SpawnNotMovableEvent.h"
#include "../common/ServerEvents/DoorOpenedEvent.h"

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
//    else if (elem >= 300 ){ // los que van a ser caminables
//        auto event = new SpawnNotMovableEvent(SpawnNotMovableType, elem, pos1, pos2);
//        newEvents.push_back(event);
//    }
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
