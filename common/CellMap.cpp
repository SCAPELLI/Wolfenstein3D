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
        double distanceWithRocket = rocket->impactPoint.distance(playerList[i].getPosition());
        playerList[i].getDamage(rocket->damage * 1/distanceWithRocket);
        if (playerList[i].isGameOver()) {
            rocket->sender->updateKills();
            AbstractEvent *event = new GameOverEvent(GameOverEventType, i);
            newEvents.push_back(event);
        }
        else if (playerList[i].isDead()){
            rocket->sender->updateKills();
            AbstractEvent* event = new KillEvent(KillEventType, i);
            newEvents.push_back(event);
            playerList[i].respawn();
        }
        else{
            AbstractEvent* event = new
                    HealthChangeEvent(HealthChangeType,
                                      rocket->damage * 1/distanceWithRocket);
            newEvents.push_back(event);
        }
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
    return !door->getEffect();
}

void CellMap::incrementCooldown(){
    door->incrementCooldown();
    for (int i = 0; i < playerList.size(); i++){
        playerList[i].incrementCooldown();
    }
}

bool CellMap::isOpenable(Player& player, std::vector<AbstractEvent*>& newEvents){
    return door ? door->isConsumed(player, newEvents) : false;
}

void CellMap::dropItems(Player& player,GameLoader& factory,
                        std::vector<AbstractEvent*>& newEvents){
    std::string ammo = "ammo";
    Item* ammoToDrop= factory.itemLoader(ammo);
    ammoToDrop += 2;
    items.push_back(ammoToDrop);
    std::string blood = "blood";
    items.push_back(factory.itemLoader(blood));
    Weapon currentWeapon = player.getWeapon();
    if (currentWeapon.name != "gun")
        currentWeapon.uniqueId = factory.assignUniqueId();
        items.push_back(&currentWeapon);
    if (player.hasKey()) {
        std::string key = "key";
        items.push_back(factory.itemLoader(key));
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