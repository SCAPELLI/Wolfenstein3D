#include "Weapon.h"
#include <bits/stdc++.h>

Weapon::Weapon(int id, int damage, int bullets, int minBullets, double speed)
    : id(id),
    damage(damage),
    bullets(bullets),
    minBullets(minBullets),
    speed(speed)
{}

int Weapon::attack(){
    if ((id == 1 || id == 2 || id == 3) && bullets < minBullets)
        return 0;
    return damage;
}

void Weapon::addBullets(int moreBullets){
    bullets += moreBullets;
}
int Weapon::getDamage()const{
    return damage;
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
