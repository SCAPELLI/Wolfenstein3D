#ifndef WOLFENSTEIN3D_PLAYER_H
#define WOLFENSTEIN3D_PLAYER_H
#include "Vector.h"
#include "Weapon.h"
#include <map>
#include "../common/Item.h"
#include <vector>
#include "../common/Items/LifeGainItem.h"
#include "../common/Items/AmmoItem.h"
#include "../common/Items/PointGainItem.h"
#include "../common/Items/KeyItem.h"


class Player {
    int id;
    Vector position;
    Vector initialPosition;
    Vector scaledPosition;
    bool dead;
    int maxBullets;
    int lifes;
    int health;
    int radius;
    double angle;
    std::map<int, Weapon> bag;
    int idWeapon;
    AmmoItem bullets;
    PointGainItem points;
    KeyItem keys;
    int prevIdWeapon;
public:
    Player(int parsed_id, Vector position);
    void lifeDecrement(int damage);
    bool hits(Player& player);
    void changeWeaponTo(int idToChange);
    double getAngle() const;
    void move(Vector& newPos);
    void rotate(double newAngle);
    int damageCurrentWeapon();
    Vector& getPosition();
    Vector& getScaledPosition();
    bool operator==(const Player& player);
    bool collideWith(Player& otherPlayer);
    bool pickupWeapon(Weapon weapon);
    void resetBagWeapons();
    Item getBullets();
    void died();
    bool isDead();
    bool isGameOver();
    bool getItem(AmmoItem* item);
    bool getItem(LifeGainItem* item);
    bool getItem(PointGainItem* item);
    bool getItem(KeyItem* item);
    bool getItem(Weapon* item);
    bool openDoor();
    Weapon getWeapon();
    bool hasKey();
    void incrementCooldown();
    void initializePlayer(bool dead);
    int getId();

};

#endif //WOLFENSTEIN3D_PLAYER_H
