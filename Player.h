#ifndef WOLFENSTEIN3D_PLAYER_H
#define WOLFENSTEIN3D_PLAYER_H
#include <string>
#include "Position.h"

class Player {
    int id;
    int life;
    Position position;
public:
    Player(std::string name);
    bool isTouched(Position& other_position);
    void move(int dx, int dy);
    Position& getPosition();
};

#endif //WOLFENSTEIN3D_PLAYER_H
