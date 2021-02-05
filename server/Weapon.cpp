#include "Weapon.h"
#include "../server/GameLoader.h"
#include <bits/stdc++.h>

Weapon::Weapon(int id, std::string name, int damage, int minBullets,
                                                            double speed)
    : id(id), effect(damage),name(name), minBullets(minBullets), speed(speed),
      Item(id, name, damage)
{}

Weapon::Weapon(int id, std::string name)
    : id(id), name (name)
{
    GameLoader yaml;
    yaml.configWeapon(name, effect, minBullets, speed);
    Item(id, name, effect);
}

int Weapon::attack(int bullets){
    if ((id == 1 || id == 2 || id == 3) && bullets < minBullets)
        return 0;
    return effect;
}
Weapon::Weapon() {}

//void Weapon::addBullets(int moreBullets){
//    bullets += moreBullets;
//}
int Weapon::getDamage()const{
    return effect;
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

bool Weapon::isConsumed(Player &player) {
    return player.getItem(this);
}

void Weapon::incrementCooldown(){}