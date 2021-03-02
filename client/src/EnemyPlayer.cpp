//
// Created by juankristal on 20/2/21.
//

#include "client/include/EnemyPlayer.h"
#define TIME_PER_IMAGE 5
#define ANIMATED_FRAMES 5
#define WALKING_TYPE 0
#define SHOOTING_TYPE 1
#define DYING_TYPE 2
#define ENEMY_TYPES 5

EnemyPlayer::EnemyPlayer(SDL_Renderer *renderer, int id, Vector spawnPoint, BagOfSprites& sprites):
    renderer(renderer), activeWeapon(1), id(id), activeAnimation(WALKING_TYPE),
    position(spawnPoint), spawnPoint(spawnPoint)
    {
        for (int i = 0; i < 3; i++) animations.emplace_back();
        for (int i = 0; i < ENEMY_TYPES; i++){
            animations[WALKING_TYPE].push_back(std::move(
                    AnimatedSprite(sprites.animationSprites[WALKING_TYPE], spawnPoint, i,
                                   ANIMATED_FRAMES, ANIMATED_FRAMES * TIME_PER_IMAGE)));
            animations[SHOOTING_TYPE].push_back(std::move(
                    AnimatedSprite(sprites.animationSprites[SHOOTING_TYPE], spawnPoint, i,
                                   ANIMATED_FRAMES, ANIMATED_FRAMES * TIME_PER_IMAGE)));
            animations[DYING_TYPE].push_back(std::move(
                    AnimatedSprite(sprites.animationSprites[DYING_TYPE], spawnPoint, i,
                                   ANIMATED_FRAMES, ANIMATED_FRAMES * TIME_PER_IMAGE)));
        }
    }

void EnemyPlayer::walkTo(Vector newPosition) {
    position = newPosition;
    for (int i = 0; i < ENEMY_TYPES; i++){
        animations[WALKING_TYPE][i].moveTo(newPosition);
        animations[SHOOTING_TYPE][i].moveTo(newPosition);
        animations[DYING_TYPE][i].moveTo(newPosition);
    }
    animations[WALKING_TYPE][activeWeapon].isAnimating = true;
    activeAnimation = WALKING_TYPE;
}

void EnemyPlayer::shoot() {
    if (animations[SHOOTING_TYPE][activeWeapon].isAnimating) return;
    animations[SHOOTING_TYPE][activeWeapon].isAnimating = true;
    activeAnimation = SHOOTING_TYPE;
}

void EnemyPlayer::changeWeapon(int idWeapon) {
    activeWeapon = idWeapon;
}
int EnemyPlayer::getActiveWeapon(){
    return activeWeapon;
}
void EnemyPlayer::die() {
    if (animations[DYING_TYPE][activeWeapon].isAnimating) return;
    animations[DYING_TYPE][activeWeapon].isAnimating = true;
    activeAnimation = DYING_TYPE;
}

void EnemyPlayer::drawFrom(Camera* origin,
                           std::vector<std::vector<int>>& map,
                           SDL_Renderer* renderer,
                           std::vector<double> &wallDistances) {
    animations[activeAnimation][activeWeapon].drawFrom(origin, map, renderer, wallDistances);
}

int EnemyPlayer::getId() {
    return id;
}

EnemyPlayer::~EnemyPlayer() {}





