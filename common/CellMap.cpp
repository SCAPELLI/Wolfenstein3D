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
Item* CellMap::removeItem() {
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

void CellMap::addItem(Item* item) {
    items.push_back(item);
}

void CellMap::setSolid() {
    occupied = true;
}

bool CellMap::isOpenable(){
//    for (auto it = items.begin(); it != items.end(); ++it){ //sino podria hacer un find con esas cosas a ver si sale true, y entonces ya sabria donde esta
//        //std::cout << (*it)->getItemName()<< std::endl;
//        if ((*it)->getItemName() == "false wall" ||  --> aca tendria qeu poner un sleep para volver a cambiar el valor dsps??
//            (*it)->getItemName() == "door" ||
//            (*it)->getItemName() == "secret passage" &&
//        (*it)->changeValue(+-1?????) -->>> poner en modo abierto ---> si es pared falsa hacer pasar al wachin pero mantenerla cerrada dsps
}

void CellMap::dropItems(Player& player){ //por enunciado deja 10 balas, cambiar el harcodeo?
    GameLoader yaml;
    items.push_back(new AmmoItem(3,"ammo", 10));
    Weapon currentWeapon = player.getWeapon();
    if (currentWeapon.name != "gun")
        items.push_back(&currentWeapon);
    if (player.hasKey())
        items.push_back(new KeyItem(KEY_ID,"key", 1));
}
void CellMap::dropItemPlayer(Item* item){
    items.push_back(item);
}
void CellMap::getItemsTile(Player& player) {
    auto it = items.begin();
    while (it != items.end()) {
        if ((*it)->isConsumed(player)) {
            it = items.erase(it);
        } else {
            ++it;
        }
    }
}