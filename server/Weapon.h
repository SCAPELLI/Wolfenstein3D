
#ifndef WEAPON_H
#define WEAPON_H


#include "../common/Item.h"
#include "Items/Rocket.h"
class Weapon : public Item{
public:
    int id;
    std::string name;
    int uniqueId;
    int presicion;
    int minBullets;
    int cooldownTimer;
    int cooldown;
    bool isShooting;

public:
    int getDamage()const;
    Weapon(int id, std::string name, int uniqueId, int damage, int minBullets, int cooldownTimer);
    //Weapon(int id, std::string name);
    Weapon();
    int attack(int bullets, int distance, double angle);
    int generateRandom();
    Rocket* launchRocket();
    //int getSpeed();
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
    bool operator<(const Weapon& t) const;
    bool operator==(const Weapon& t) const;
    void incrementCooldown();
    bool canShoot(int bullets);
    bool doesHit(int distance, double angle);
};

#endif //WOLFENSTEIN3D_WEAPON_H
