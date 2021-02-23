

#ifndef CAMERA_CPP_Rocket_H
#define CAMERA_CPP_Rocket_H


#include "client/Vector.h"
class Player;
class Rocket {
public:
    Vector impactPoint;
    Player* sender;
    int damage;
    Rocket(int damage);

};


#endif //CAMERA_CPP_Rocket_H
