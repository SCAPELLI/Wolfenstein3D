#ifndef WOLFENSTEIN3D_PLAYER_H
#define WOLFENSTEIN3D_PLAYER_H
#include <string>
#include "Vector.h"

class Player {
    int id;
    int lifes;
    int health;
    int radius;
    int angle;
    Vector position;
public:
    Player(int parsed_id, Vector position);
    Player();
//    Player(Player&& otherPlayer);
//    Player& operator=(Player&& other)noexcept;
    bool isTouched(Vector& otherPosition);
    void move(Vector& newPos);
    Vector& getPosition();
    bool collideWith(Player& otherPlayer);
};

#endif //WOLFENSTEIN3D_PLAYER_H
