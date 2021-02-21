#include "AnimatedSprite.h"
#include "SDL2/SDL_image.h"

#define FILE_EXTENTION ".bmp"

AnimatedSprite::AnimatedSprite(std::map<std::pair<int, int>, Sprite>& sprites, Vector pos, int animationId,
                               int amountOfFrames, int animatedTime):
    animatedTime(animatedTime),
    currentTime(0){
        for (int i = 0; i < amountOfFrames; i++) {
            this->sprites.push_back(std::move(Renderable(pos.x, pos.y, &sprites[std::make_pair(animationId, i)])));
        }
        this->isAnimating = false;
}

void AnimatedSprite::moveTo(Vector& newPos){
    for (int i = 0; i < sprites.size(); i++){
        sprites[i].moveTo(newPos);
    }
}

void AnimatedSprite::draw(SDL_Renderer* renderer, int posX, int posY, int scale){
    int framesPerImage = int(animatedTime / sprites.size());
    int frameToDraw = int(currentTime / framesPerImage);
    sprites[frameToDraw].drawOnScreen(renderer, posX, posY, scale);
    currentTime += 1;
    currentTime %= animatedTime;
    if (isAnimating == false){
        currentTime = 0;
    }
    if (currentTime == 0){
        isAnimating = false;
    }
}

void AnimatedSprite::drawFrom(Camera* origin,
                             std::vector<std::vector<int>>& map,
                             SDL_Renderer* renderer,
                             std::vector<double> &wallDistances){
    int framesPerImage = int(animatedTime / sprites.size());
    int frameToDraw = int(currentTime / framesPerImage);
    sprites[frameToDraw].drawFrom(origin, map, renderer,wallDistances);
    currentTime += 1;
    currentTime %= animatedTime;
    if (isAnimating == false){
        currentTime = 0;
    }
    if (currentTime == 0){
        isAnimating = false;
    }
}

AnimatedSprite::~AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(AnimatedSprite &&other):
    animatedTime(other.animatedTime), currentTime(other.currentTime),
    sprites(std::move(other.sprites)), isAnimating(other.isAnimating){}

AnimatedSprite &AnimatedSprite::operator=(AnimatedSprite &&other) {
    animatedTime = std::move(other.animatedTime);
    currentTime = std::move(other.currentTime);
    sprites = std::move(other.sprites);
    isAnimating = other.isAnimating;
    return *this;
}

AnimatedSprite::AnimatedSprite() {}
