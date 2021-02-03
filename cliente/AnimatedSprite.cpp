#include "AnimatedSprite.h"
#include "SDL2/SDL_image.h"

#define FILE_EXTENTION ".png"

AnimatedSprite::AnimatedSprite(const std::string &path, SDL_Renderer *renderer, int amountOfFrames, int animatedTime):
    animatedTime(animatedTime),
    currentTime(0) {
        for (int i = 0; i < amountOfFrames; i++) {
            this->sprites.emplace_back(Sprite(path + std::to_string(i) + FILE_EXTENTION, renderer)); // maybe leak, maybe use new, missing .png
        }
}

void AnimatedSprite::draw(SDL_Renderer *renderer, int x, double distance) {
    int framesPerImage = int(animatedTime / sprites.size());
    int frameToDraw = int(currentTime / framesPerImage);
    //sprites[frameToDraw].draw(renderer, x, distance);
    currentTime += 1;
    currentTime %= animatedTime;
}

AnimatedSprite::~AnimatedSprite() {}