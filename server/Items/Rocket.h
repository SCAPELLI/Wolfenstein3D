

#ifndef CAMERA_CPP_Rocket_H
#define CAMERA_CPP_Rocket_H
#include <vector>
#include "../../common/include/AbstractEvent.h"
#include "../include/Item.h"
#include "server/include/Vector.h"
class Player;
class Rocket : public Item {
public:
    Vector impactPoint;
    int sender;
    int damage;
    Vector currentPosition;
    Vector direction;
    Rocket(int id, std::string name, int effect, int uniqueId);
    void moveRocket(std::vector<AbstractEvent*>& newEvents);
    Vector getPositionScaled();

};


#endif //CAMERA_CPP_Rocket_H
