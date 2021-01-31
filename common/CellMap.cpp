#include "CellMap.h"
#include "Item.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "Items/LockedDoor.h"
#include "GameLoader.h"
#include "Items/AmmoItem.h"
#define KEY_ID 101
#define GUN_ID 2


CellMap::CellMap()
: occupied(false), items(), playerList(){}


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
    GameLoader yaml;
    items.push_back(AmmoItem(3,"bullets", 10));
    Weapon currentWeapon = player.getWeapon();
    if (currentWeapon.id != GUN_ID) // CAMBIAR ESTE HARCODEO TMB
        items.push_back(currentWeapon);
    if (player.hasKey())
        items.push_back(KeyItem(KEY_ID,"key", 1));
}
void CellMap::dropItemPlayer(Item item){
    items.push_back(item);
}
void CellMap::getItemsTile(Player& player) {
    for (auto it = items.begin(); it != items.end(); ++it){
        std::cout << it->getItemName()<< std::endl;
        if (it->getItemName() == "false wall" &&
            it->getItemName() == "door" &&
            it->getItemName() == "locked door" &&
            it->getItemName() == "secret passage" &&
            player.getItem(*it)) {
            items.erase(it);
        }
    }
}