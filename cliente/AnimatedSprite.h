#ifndef WOLF_ANIMATEDSPRITE_H
#define WOLF_ANIMATEDSPRITE_H

#include <string>
#include <vector>
#include "Sprite.h"
#include "SDL2/SDL.h"


class AnimatedSprite {
    int animatedTime, currentTime;
    std::vector<Sprite*> sprites;
    public:
        bool isAnimating;
        AnimatedSprite(const std::string& path, SDL_Renderer* renderer, int amountOfFrames, int animatedTime);
        void draw(SDL_Renderer* renderer, int posX, int posY, int scale);
        void rayCast(SDL_Renderer* renderer, double posX, double posY, std::vector<double> &wallDistances);
        ~AnimatedSprite();
};


#endif //WOLF_ANIMATEDSPRITE_H
