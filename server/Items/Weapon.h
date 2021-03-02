
#ifndef WEAPON_H
#define WEAPON_H


#include "server/include/Item.h"
#include "Rocket.h"
class Weapon : public Item{
public:
    int id;
    std::string name;
    int uniqueId;
    int precision;
    int minBullets;
    int cooldownTimer;
    int cooldown;
    bool isShooting;

public:
    int getDamage()const;
    Weapon(int id, std::string& name, int uniqueId, int damage, int minBullets, int cooldownTimer);
    Weapon();
    int attack( int distance, double angle);
    int generateRandom();
    void setDamageByRocketLauncher(Rocket* rocket);
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
    bool operator<(const Weapon& t) const;
    bool operator==(const Weapon& t) const;
    void incrementCooldown();
    bool canShoot(int bullets);
    bool doesHit(int distance, double angle);
};

#endif //WOLFENSTEIN3D_WEAPON_H
