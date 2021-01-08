#include "CellMap.h"
#include "Item.h"
#include "Player.h"
#include <vector>
#include <iostream>
#define BULLET_ID 100
#define KEY_ID 101

CellMap::CellMap()
: occupied(false), player(nullptr), items(){}


void CellMap::transferPlayer(CellMap& other){
    this->player = other.player;
    other.player = nullptr;
}

void CellMap::removePlayer() {
    dropItems();
    player = nullptr;
}

void CellMap::addPlayer(Player *setPlayer) {
    this->player = setPlayer;
}

bool CellMap::hasPlayer() {
    return player;
}
Item CellMap::removeItem() {
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

void CellMap::addItem(Item item) {
    items.push_back(item);
}

void CellMap::setSolid() {
    occupied = true;
}

void CellMap::dropItems(){
    items.push_back(Item(BULLET_ID, 10));
    items.push_back(player->getWeapon());
    if (player->hasKey())
        items.push_back(Item(KEY_ID, 1));
}
void CellMap::dropItemPlayer(Item item){
    items.push_back(item);
}
void CellMap::getItemsTile() {
    for (auto it = items.begin(); it != items.end(); ++it){
        if (player->getItem(it->getItemId()))
            items.erase(it);
    }
}