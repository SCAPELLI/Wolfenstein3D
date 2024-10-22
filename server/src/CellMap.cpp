#include "server/include/CellMap.h"
#include "server/include/Item.h"
#include "server/include/Player.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <common/ServerEvents/HealthChangeEvent.h>
#include <common/ServerEvents/KillEvent.h>
#include <common/ServerEvents/GameOverEvent.h>
#include "server/Items/LockedDoor.h"
#include "server/include/GameLoader.h"
#include "common/ServerEvents/DespawnEvent.h"
#include "common/ServerEvents/SpawnEvent.h"



CellMap::CellMap()
: occupied(false), items(), playerList(), door(nullptr){}

void CellMap::removeResources() {
    for (auto& item: items) {
        delete item;
    }
    delete door;
}

void CellMap::removePlayer(Player& player) {
    auto index = std::find(playerList.begin(), playerList.end(), player);
    if (index == playerList.end()) return;
    playerList.erase(index);
}

void CellMap::addPlayer(Player& setPlayer) {
    if (std::find(playerList.begin(), playerList.end(), setPlayer) != playerList.end())
        return;
     playerList.emplace_back(setPlayer);
}


bool CellMap::isSolid(){
    return occupied;
}

bool CellMap::impacts(Rocket* rocket, std::vector<int>& damagedPlayers) {
    if(occupied || door != nullptr) return true;
    for (int i = 0; i < playerList.size(); i++){
        if (playerList[i].getId() != rocket->sender){
            rocket->impactPoint = playerList[i].getPosition();
            damagedPlayers.push_back(playerList[i].getId());
        }
    }
    return !damagedPlayers.empty();
}

void CellMap::explode(Rocket* rocket, std::vector<int>& damagedPlayers) {
    if(occupied || door != nullptr) return;
    for (int i = 0; i < playerList.size(); i++){
        damagedPlayers.push_back(playerList[i].getId());
    }
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
    return door->getEffect() != 0;
}

void CellMap::incrementCooldown(){
    door->incrementCooldown();
    for (int i = 0; i < playerList.size(); i++){
        playerList[i].incrementCooldown();
    }
}

bool CellMap::isOpenable(Player& player, std::vector<AbstractEvent*>& newEvents){
    return door != nullptr && door->isConsumed(player, newEvents);
}

void CellMap::dropItems(Player& player,GameLoader& factory,
                        std::vector<AbstractEvent*>& newEvents){
    Vector pos = player.getPosition();
    std::string ammo = "ammo";
    Item* ammoToDrop= factory.itemLoader(ammo);
    ammoToDrop->changeValue(5);
    items.push_back(ammoToDrop);
    auto* event = new SpawnEvent(SpawnEventType, ammoToDrop->getUniqueId(),
                                   ammoToDrop->getId(), pos.y , pos.x );
    newEvents.push_back(event);
    std::string blood = "blood";
    Item* bloodDropped = factory.itemLoader(blood);
    items.push_back(bloodDropped);
    auto* event1 = new SpawnEvent(SpawnEventType, bloodDropped->getUniqueId(),
                                 bloodDropped->getId(), pos.y , pos.x );
    newEvents.push_back(event1);
    Weapon currentWeapon = player.getWeapon();
    if (currentWeapon.name != "pistol" && currentWeapon.name != "knife") {
        Item* weaponTodrop = factory.weaponLoader(currentWeapon.name);
        items.push_back(weaponTodrop);
        player.eraseCurrentWeapon();
        auto *event2 = new SpawnEvent(SpawnEventType, weaponTodrop->getUniqueId(),
                                      weaponTodrop->getId() + WEAPONSGAP, pos.y , pos.x );
        newEvents.push_back(event2);
    }
    if (player.hasKey()) {
        std::string key = "key";
        Item* keyToDrop = factory.itemLoader(key);
        items.push_back(keyToDrop);
        auto* event3 = new SpawnEvent(SpawnEventType, keyToDrop->getUniqueId(),
                                      keyToDrop->getId(), pos.y , pos.x );
        newEvents.push_back(event3);
    }
}
OpenableItem* CellMap::getDoor() {
    return door;
}
bool CellMap::isLockedDoor(){
    return door != nullptr && door->getItemName() == "locked door";
}

void CellMap::getItemsTile(Player& player,
                            std::vector<AbstractEvent*>& newEvents) {
    //ignorar en caso de ser bot
    if (player.getId() == 0) return;
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