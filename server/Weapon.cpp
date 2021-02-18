#include "Weapon.h"
#include "../server/GameLoader.h"
#include "Player.h"
#include <bits/stdc++.h>
#include "Constants.h"
Weapon::Weapon(int id, std::string name, int uniqueId, int damage,
               int minBullets, int cooldownTimer)
    : id(id), uniqueId(uniqueId), presicion(damage),name(name),
    minBullets(minBullets), cooldown(0), cooldownTimer(cooldownTimer),
    isShooting(false), Item(id, name, damage, uniqueId)// arreglar nombres ffs
{}



int Weapon::generateRandom(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 10);
    return distr(gen);
}

int Weapon::attack(int bullets, int distance, double angle){ // ver con la presicion
    if (id == Knife){
        return generateRandom();
    }
    return generateRandom() * 1/angle * (1/(double)distance) * minBullets;  //acotar daÑo a un max y * #balas
}

int Weapon::launchRocket(int distance){
    return generateRandom() * 1/distance;
}
bool Weapon::canShoot(int bullets, int distance, double angle){
   return (generateRandom() * 1/(double)distance * (1/angle) >= presicion) &&
            bullets >= minBullets && !isShooting;
}

Weapon::Weapon() {
}


int Weapon::getDamage()const {
    return presicion;
}
bool Weapon::operator<(const Weapon& t) const{
    return (this->id < t.id);
}
bool Weapon::operator==(const Weapon& t) const{
    return (this->name == t.name);
}

bool Weapon::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}

void Weapon::incrementCooldown(){ //decrease
    if (isShooting) {
        cooldown += 1;
        cooldown %= cooldownTimer;
    }
    if (cooldown == 0){
        isShooting = false;
    }
}