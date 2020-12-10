#ifndef WOLFENSTEIN3D_PLAYER_H
#define WOLFENSTEIN3D_PLAYER_H
#include <string>
#include "Vector.h"
#include "Weapon.h"
#include "Gun.h"

class Player {
    int id;
    int lifes;
    int health;
    int radius;
    int angle;
    Vector position;
    Weapon* weapon;
public:
    Player(int parsed_id, Vector position);
    Player();
    void lifeDecrement(int damage);
    Player(Player&& otherPlayer);
    Player& operator=(Player&& other)noexcept;
    //Player& operator = (const Player& other) = delete;
    bool isTouched(Vector& otherPosition);
    void move(Vector& newPos);
    void rotate(int newAngle);
    Vector& getPosition();
    bool collideWith(Player& otherPlayer);
};

#endif //WOLFENSTEIN3D_PLAYER_H
