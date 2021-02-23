#ifndef WOLF_ANIMATEDSPRITE_H
#define WOLF_ANIMATEDSPRITE_H

#include <string>
#include <vector>
#include <map>
#include "Renderable.h"
#include "SDL2/SDL.h"

/*Clase que anima los sprites*/
class AnimatedSprite {
    int animatedTime, currentTime;
    std::vector<Renderable> sprites;
    public:
        bool isAnimating;
        AnimatedSprite();
        AnimatedSprite(const AnimatedSprite&) = delete;
        AnimatedSprite& operator=(const AnimatedSprite&) = delete;
        AnimatedSprite(AnimatedSprite&& other);
        AnimatedSprite& operator=(AnimatedSprite&& other);
        AnimatedSprite(std::map<std::pair<int, int>, Sprite>& sprites, Vector pos, int animationId,
                       int amountOfFrames, int animatedTime);
        void draw(SDL_Renderer* renderer, int posX, int posY, int scale);
        void moveTo(Vector& newPos);
        void drawFrom(Camera* origin,
                     std::vector<std::vector<int>>& map,
                     SDL_Renderer* renderer,
                     std::vector<double> &wallDistances);
        ~AnimatedSprite();
};


#endif //WOLF_ANIMATEDSPRITE_H
