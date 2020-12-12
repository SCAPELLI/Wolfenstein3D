#include "Weapon.h"


Weapon::Weapon(int id, int damage)
    : id(id), damage(damage)
{}

void Weapon::attack(){
}

Weapon::Weapon(Weapon &&other) {}