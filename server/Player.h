#ifndef WOLFENSTEIN3D_PLAYER_H
#define WOLFENSTEIN3D_PLAYER_H
#include "Vector.h"
#include "Weapon.h"
#include <map>
#include "Gun.h"

class Player {
    int id;
    Vector position;
    Vector initialPosition;
    bool gameOver = false;
    int lifes;
    int health;
    int radius;
    double angle;
    std::map<Weapon, bool> bag;
public:
    Player(int parsed_id, Vector position);
    int lifeDecrement(int damage);
    bool hits(Player& player);
    void changeWeaponTo(Weapon weapon);
    double getAngle() const;
    void move(Vector& newPos);
    void rotate(double newAngle);
    int damageCurrentWeapon();
    Vector& getPosition();
    bool collideWith(Player& otherPlayer);
    void pickupWeapon(Weapon weapon);
    void resetBagWeapons();
    void died();
};

#endif //WOLFENSTEIN3D_PLAYER_H
