
#ifndef WOLFENSTEIN3D_WEAPON_H
#define WOLFENSTEIN3D_WEAPON_H


#include "../common/Item.h"

class Weapon : public Item{
public:
    int id;
    int effect;
    int minBullets;
    double speed;

public:
    int getDamage()const;
    Weapon(int id, int damage, int minBullets, double speed);
    Weapon();
    int attack(int bullets);
    int getSpeed();
    bool operator<(const Weapon& t) const;
    bool operator==(const Weapon& t) const;
};

#endif //WOLFENSTEIN3D_WEAPON_H
