#include "AnimatedSprite.h"
#include "SDL2/SDL_image.h"

#define FILE_EXTENTION ".bmp"

AnimatedSprite::AnimatedSprite(const std::string &path, SDL_Renderer *renderer, int amountOfFrames, int animatedTime):
    animatedTime(animatedTime),
    currentTime(0){
        for (int i = 0; i < amountOfFrames; i++) {
            this->sprites.emplace_back(new Sprite(path + std::to_string(i) + FILE_EXTENTION, renderer)); // maybe leak, maybe use new, missing .png
        }
        this->isAnimating = false;
}

void AnimatedSprite::draw(SDL_Renderer* renderer, int posX, int posY, int scale){
    int framesPerImage = int(animatedTime / sprites.size());
    int frameToDraw = int(currentTime / framesPerImage);
    sprites[frameToDraw]->draw(renderer, posX, posY, scale);
    currentTime += 1;
    currentTime %= animatedTime;
    if (isAnimating == false){
        currentTime = 0;
    }
    if (currentTime == 0){
        isAnimating = false;
    }
}

void AnimatedSprite::rayCast(SDL_Renderer* renderer, double posX, double posY, std::vector<double> &wallDistances){
    int framesPerImage = int(animatedTime / sprites.size());
    int frameToDraw = int(currentTime / framesPerImage);
    sprites[frameToDraw]->rayCast(renderer, posX, posY, wallDistances);
    currentTime += 1;
    currentTime %= animatedTime;
    if (isAnimating == false){
        currentTime = 0;
    }
    if (currentTime == 0){
        isAnimating = false;
    }
}

AnimatedSprite::~AnimatedSprite() {
    for (int i = 0; i < sprites.size(); i++) delete sprites[i];
}