#include "Weapon.h"
#include <bits/stdc++.h>
#include "Constants.h"
#include "Items/Rocket.h"
#include "Player.h"
#include <cmath>
Weapon::Weapon(int id, std::string name, int uniqueId, int damage,
               int minBullets, int cooldownTimer)
    : id(id), uniqueId(uniqueId), precision(damage),name(name),
    minBullets(minBullets), cooldown(0), cooldownTimer(cooldownTimer),
    isShooting(false), Item(id, name, damage, uniqueId)
{}



int Weapon::generateRandom(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 10);
    return distr(gen);
}

int Weapon::attack( int distance, double angle){
    if (id == Knife){
        return generateRandom();
    }
    int damage = generateRandom() * 1/std::abs(angle) * (30/(double)distance) * minBullets;  //acotar daÑo a un max
    int acot = damage % (10 * minBullets);
    return acot;

}

Rocket* Weapon::launchRocket(){
    int damage = generateRandom();
    return new Rocket(damage);
}

bool Weapon::doesHit(int distance, double angle){ // doesHit
   return true;
//   (generateRandom() * 100/(double)distance * (1/angle) >= precision);
}

bool Weapon::canShoot(int bullets){
    return bullets >= minBullets && !isShooting;
}

Weapon::Weapon() {
}



int Weapon::getDamage()const {
    return precision;
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
    if (cooldown == cooldownTimer){
        isShooting = false;
    }
}