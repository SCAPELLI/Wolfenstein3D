#ifndef WOLF_BAGOFSPRITES_H
#define WOLF_BAGOFSPRITES_H

#include <map>
#include "Sprite.h"

class BagOfSprites {
    public:
        std::map<int, Sprite> items;
        BagOfSprites(SDL_Renderer* renderer);
        ~BagOfSprites();
};


#endif //WOLF_BAGOFSPRITES_H
