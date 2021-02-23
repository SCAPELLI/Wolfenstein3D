#ifndef WOLF_BAGOFSPRITES_H
#define WOLF_BAGOFSPRITES_H

#include <map>
#include "Sprite.h"
#include <vector>
/* Bolsa donde se guardan los sprites que son utilizados*/
class BagOfSprites {
    public:
        std::map<int, Sprite> items;
        std::map<int, std::map<std::pair<int, int>, Sprite>> animationSprites;
        std::map<std::pair<int,int>, Sprite> weaponSprites;
        BagOfSprites(SDL_Renderer* renderer);
        ~BagOfSprites();
};


#endif //WOLF_BAGOFSPRITES_H
