#include "CellMap.h"
#include "Item.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <ServerEvents/HealthChangeEvent.h>
#include <ServerEvents/KillEvent.h>
#include <ServerEvents/GameOverEvent.h>
#include "Items/LockedDoor.h"
#include "GameLoader.h"
#include "Items/AmmoItem.h"
#include "ServerEvents/DespawnEvent.h"
#include "ServerEvents/SpawnEvent.h"



CellMap::CellMap()
: occupied(false), items(), playerList(), door(nullptr){}


void CellMap::removePlayer(Player& player) { //deberia recibir el player
    //dropItems(player);
    auto index = std::find(playerList.begin(), playerList.end(), player);
    if (index == playerList.end()) return;
    playerList.erase(index);
}

void CellMap::addPlayer(Player& setPlayer) {
    if (std::find(playerList.begin(), playerList.end(), setPlayer) != playerList.end())
        return;
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

bool CellMap::impacts(Rocket* rocket, std::vector<AbstractEvent*>& newEvents){
    for (int i = 0; i < playerList.size(); i++){
        if (playerList[i].getId() != rocket->sender->getId()){
            rocket->impactPoint = playerList[i].getPosition();
            playerList[i].getDamage(rocket->damage);
            return true;
        }
    }
    return false;
}

void CellMap::explode(Rocket* rocket, std::vector<AbstractEvent *> &newEvents) {
    if(occupied) return;
    for (int i = 0; i < playerList.size(); i++){
        return;
//        double distanceWithRocket = rocket->impactPoint.distance(playerList[i].getPosition());
//        playerList[i].getDamage(rocket->damage * 1/distanceWithRocket);
//        if (playerList[i].isGameOver()) {
//            rocket->sender->updateKills();
//            AbstractEvent *event = new GameOverEvent(GameOverEventType, i );
//            newEvents.push_back(event);
//        }
//        else if (playerList[i].isDead()){
//            rocket->sender->updateKills();
//            AbstractEvent* event = new KillEvent(KillEventType, i);
//            newEvents.push_back(event);
//            playerList[i].respawn();
//        }
//        else{
//            AbstractEvent* event = new
//                    HealthChangeEvent(HealthChangeType,
//                                      rocket->damage * 1/distanceWithRocket);
//            newEvents.push_back(event);
//        }
    }
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
                                      weaponTodrop->getId() + 49, pos.y , pos.x );
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
void CellMap::dropItemPlayer(Item* item){
    items.push_back(item);
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