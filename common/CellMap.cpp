#include "CellMap.h"
#include "Item.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "Items/LockedDoor.h"
#include "GameLoader.h"
#include "Items/AmmoItem.h"
#include "ServerEvents/DespawnEvent.h"



CellMap::CellMap()
: occupied(false), items(), playerList(), door(nullptr){}


void CellMap::removePlayer(Player& player) { //deberia recibir el player
    //dropItems(player);
    auto index = std::find(playerList.begin(), playerList.end(), player);
    if (index != playerList.end()) return;
    playerList.erase(index);
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
void CellMap::addItem(OpenableItem* item) {
    door = item;
}
void CellMap::addItem(Item* item) {
    items.push_back(item);
}

void CellMap::setSolid() {
    occupied = true;
}
bool CellMap::isOpen(){
    if (door == nullptr) return true;
    return !door->getEffect();
}

void CellMap::incrementCooldown(){
    door->incrementCooldown();
    for (int i = 0; i < playerList.size(); i++){
        playerList[i].incrementCooldown();
    }
}

bool CellMap::isOpenable(Player& player, std::vector<AbstractEvent*>& newEvents){
    return door->isConsumed(player, newEvents);
}

void CellMap::dropItems(Player& player){ //poner spawneo, cambiar el harcodeo?
    GameLoader yaml;
    items.push_back(new AmmoItem(3,"ammo", 10, 0));
    std::string blood = "blood";
    items.push_back(yaml.itemLoader(blood));
    Weapon currentWeapon = player.getWeapon();
    if (currentWeapon.name != "gun")
        items.push_back(&currentWeapon);
    if (player.hasKey()) {
        std::string key = "key";
        items.push_back(yaml.itemLoader(key));
    }
}
void CellMap::dropItemPlayer(Item* item){
    items.push_back(item);
}
void CellMap::getItemsTile(Player& player,
                            std::vector<AbstractEvent*>& newEvents) {
    auto it = items.begin();
    while (it != items.end()) {
        if ((*it)->isConsumed(player, newEvents)) {
            auto* event = new DespawnEvent(DespawnEventType, (*it)->getUniqueId(),
                                                   (*it)->getId());
            newEvents.push_back(event);
            delete(*it);
            it = items.erase(it);
        } else {
            ++it;
        }
    }
}