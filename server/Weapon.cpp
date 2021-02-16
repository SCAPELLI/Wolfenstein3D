#include "Weapon.h"
#include "../server/GameLoader.h"
#include "Player.h"
#include <bits/stdc++.h>

Weapon::Weapon(int id, std::string name, int uniqueId, int damage,
               int minBullets, double speed)
    : id(id), uniqueId(uniqueId), presicion(damage),name(name),
    minBullets(minBullets), speed(speed), Item(id, name, damage, uniqueId)
{}

Weapon::Weapon(int id, std::string name)
    : id(id), name (name)
{
    GameLoader yaml;
    yaml.configWeapon(name, presicion, minBullets, speed);
    Item(id, name, presicion, 0);
}

int Weapon::generateRandom(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 10);
    return distr(gen);
}

int Weapon::attack(int bullets, int distance, int angle){ // ver con la presicion
    if ((id == 1 || id == 2 || id == 3 || id == 4) && bullets > minBullets) //borrar esto?
        return 0;
    if (id == 4)
       return launchRocket(distance);
    if (id == 0){
        return generateRandom();
    }
    return  generateRandom() * presicion * angle * (1/distance);
}

int Weapon::launchRocket(int distance){
    return generateRandom() * 1/distance;
}

Weapon::Weapon() {}


int Weapon::getDamage()const{
    return presicion;
}
int Weapon::getSpeed(){
    return speed;
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

void Weapon::incrementCooldown(){}