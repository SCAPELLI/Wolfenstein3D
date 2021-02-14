
#ifndef WEAPON_H
#define WEAPON_H


#include "../common/Item.h"

class Weapon : public Item{
public:
    int id;
    std::string name;
    int presicion;
    int minBullets;
    double speed;
    int cooldown;

public:
    int getDamage()const;
    Weapon(int id, std::string name,int damage, int minBullets, double speed);
    Weapon(int id, std::string name);
    Weapon();
    int attack(int bullets, int distance, int angle);
    int generateRandom();
    int launchRocket(int distance);
    int getSpeed();
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
    bool operator<(const Weapon& t) const;
    bool operator==(const Weapon& t) const;
    void incrementCooldown();
};

#endif //WOLFENSTEIN3D_WEAPON_H
