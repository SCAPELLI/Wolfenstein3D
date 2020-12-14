#ifndef WOLFENSTEIN3D_PLAYER_H
#define WOLFENSTEIN3D_PLAYER_H
#include <string>
#include "Vector.h"
#include "Weapon.h"
#include <map>
#include "Gun.h"

class Player {
    int id;
    Vector position;
    int lifes;
    int health;
    int radius;
    double angle;
    std::map<int, Weapon&> bag;
public:
    Player(int parsed_id, Vector position);
    //Player(Player player);
    int lifeDecrement(int damage);
    //Player(const Player& otherPlayer);
//    Player& operator=(Player&& other)noexcept;
    //Player& operator = (const Player& other) = delete;
   // bool isTouched(Vector& otherPosition);
    bool hits(Player& player);
    double getAngle() const;
    void move(Vector& newPos);
    void rotate(double newAngle);
    Vector& getPosition();
    bool collideWith(Player& otherPlayer);
};

#endif //WOLFENSTEIN3D_PLAYER_H
