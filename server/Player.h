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
    bool gameOver;
    int coins;
    int keys;
    int lifes;
    int health;
    int radius;
    double angle;
    std::map<int, Weapon> bag;
    int idWeapon;
    std::map<int, Weapon>items;
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
    bool collideWith(Player& otherPlayer);
    void pickupWeapon(Weapon weapon);
    void resetBagWeapons();
    void died();
    bool isGameOver();
    void getItem(int idItem);
    bool openDoor();
};

#endif //WOLFENSTEIN3D_PLAYER_H