
#ifndef WEAPON_H
#define WEAPON_H


#include "../common/Item.h"

class Weapon : public Item{
public:
    int id;
    std::string name;
    int effect;
    int minBullets;
    double speed;

public:
    int getDamage()const;
    Weapon(int id, std::string name,int damage, int minBullets, double speed);
    Weapon(int id, std::string name);
    Weapon();
    int attack(int bullets);
    int getSpeed();
    bool isConsumed(Player& player) override;
    bool operator<(const Weapon& t) const;
    bool operator==(const Weapon& t) const;
};

#endif //WOLFENSTEIN3D_WEAPON_H
