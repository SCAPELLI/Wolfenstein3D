#include "Weapon.h"


Weapon::Weapon(int id, int damage, int bullets, int minBullets, int speed)
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

int Weapon::getSpeed(){
    return speed;
}

Weapon::Weapon(Weapon &&other) {}