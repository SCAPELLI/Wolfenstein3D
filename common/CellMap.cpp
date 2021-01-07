#include "CellMap.h"
#include "Item.h"
#include "Player.h"
#include <vector>


CellMap::CellMap()
: occupied(false), player(nullptr), items(){}


void CellMap::transferPlayer(CellMap& other){
    player = other.player;
    other.player = nullptr;
}

void CellMap::removePlayer() {
    // ver si aca droppeo las cosas del player
    player = nullptr;
}

void CellMap::addPlayer(Player *setPlayer) {
    this->player = setPlayer;
}

bool CellMap::hasPlayer() {
    return player;
}
Item* CellMap::removeItem() {
    return items.back();
}

bool CellMap::isSolid(){
    return occupied;
}

Player* CellMap::getPlayer() {
    return player;
}

bool CellMap::hasItems() {
    if (items.size() == 0)
        return false;
    return true;
}

void CellMap::addItem(Item* item) {
    items.push_back(item);
}

void CellMap::setSolid() {
    occupied = true;
}