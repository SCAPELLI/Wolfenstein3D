#ifndef WOLF_ANIMATEDSPRITE_H
#define WOLF_ANIMATEDSPRITE_H

#include <string>
#include <vector>
#include "Sprite.h"
#include "SDL2/SDL.h"


class AnimatedSprite {
    int animatedTime, currentTime, h, w;
    std::vector<Sprite> sprites;
    public:
        AnimatedSprite(const std::string& path, SDL_Renderer* renderer, int , int animatedTime);
        void draw(SDL_Renderer* renderer, int x, double distance);
        ~AnimatedSprite();
};


#endif //WOLF_ANIMATEDSPRITE_H
