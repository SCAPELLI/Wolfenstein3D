#ifndef WOLF_CWEAPON_H
#define WOLF_CWEAPON_H

#include "AnimatedSprite.h"

class CWeapon {
    AnimatedSprite animatedSprite;
    public:
        CWeapon(int weaponID, std::map<std::pair<int, int>, Sprite>& sprites);
        bool shoot();
        void draw(SDL_Renderer* renderer, int posX, int posY, int scale);
        ~CWeapon();
};


#endif
