#ifndef WOLFENSTEIN3D_KNIFE_H
#define WOLFENSTEIN3D_KNIFE_H
#include "Weapon.h"
class weapon;

class Knife: public Weapon {
public:
    Knife();
    void attack() override;
};


#endif //WOLFENSTEIN3D_KNIFE_H
