#ifndef WOLF_CWEAPON_H
#define WOLF_CWEAPON_H

#include "AnimatedSprite.h"

class CWeapon {
    AnimatedSprite animatedSprite;
    public:
        CWeapon(int weaponID, SDL_Renderer *renderer);
        bool shoot();
        void draw(SDL_Renderer* renderer, int posX, int posY, int scale);
        ~CWeapon();
};


#endif
