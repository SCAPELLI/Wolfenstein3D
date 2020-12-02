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
    Player(int parsed_id, int init_x, int init_y);
    bool isTouched(Vector& other_position);
    void move(int dx, int dy);
    Vector& getPosition();
    bool collideWith(Player& other_player);
};

#endif //WOLFENSTEIN3D_PLAYER_H
