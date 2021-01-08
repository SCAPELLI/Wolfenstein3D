#include "Weapon.h"
#include <bits/stdc++.h>

Weapon::Weapon(int id, int damage, int minBullets, double speed)
    : id(id),
    effect(damage),
    minBullets(minBullets),
    speed(speed)
{}

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
    return (this->id == t.id);
}
