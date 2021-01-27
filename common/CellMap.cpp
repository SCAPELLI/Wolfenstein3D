#include "CellMap.h"
#include "Item.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <algorithm>
#define BULLET_ID 100
#define KEY_ID 101
#define GUN_ID 2


CellMap::CellMap()
: occupied(false), items(), playerList(){}


//void CellMap::transferPlayer(CellMap& other){ //borrar?
//    this->player = other.player;
//    other.player = nullptr;
//}

void CellMap::removePlayer(Player& player) { //deberia recibir el player
    //dropItems(player);
    auto index = std::find(playerList.begin(), playerList.end(), player);
    if (index != playerList.end()) return;
    playerList.erase(index); //find y borrar
}

void CellMap::addPlayer(Player& setPlayer) {
     playerList.emplace_back(setPlayer);
}

bool CellMap::hasPlayer() {
    return playerList.size();
}
Item CellMap::removeItem() {
    return items.back();
}

bool CellMap::isSolid(){
    return occupied;
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

void CellMap::dropItems(Player& player){ //por enunciado deja 10 balas, cambiar el harcodeo
    items.push_back(Item(BULLET_ID, 10));
    Weapon currentWeapon = player.getWeapon();
    if (currentWeapon.id != GUN_ID) // CAMBIAR ESTE HARCODEO TMB
        items.push_back((Item) currentWeapon);
    if (player.hasKey())
        items.push_back(Item(KEY_ID, 1));
}
void CellMap::dropItemPlayer(Item item){
    items.push_back(item);
}
void CellMap::getItemsTile(Player& player) {
    for (auto it = items.begin(); it != items.end(); ++it){
        if (player.getItem(it->getItemId()))
            items.erase(it);
    }
}