//
// Created by juankristal on 20/2/21.
//

#include "EnemyPlayer.h"
#define WALK_PATH "../cliente/sprites/enemy_sprites/walking/1-"
#define SHOOT_PATH "../cliente/sprites/enemy_sprites/shooting/1-"
#define DYING_PATH "../cliente/sprites/enemy_sprites/dying/1-"
#define TIME_PER_IMAGE 5
#define ANIMATED_FRAMES 5
#define WALKING_TYPE 0
#define SHOOTING_TYPE 1
#define DYING_TYPE 2
#define ENEMY_TYPES 5

EnemyPlayer::EnemyPlayer(SDL_Renderer *renderer, int id, Vector spawnPoint, BagOfSprites& sprites):
    renderer(renderer), activeWeapon(1), id(id), position(spawnPoint), spawnPoint(spawnPoint) // active animation
    {
        for (int i = 0; i < ENEMY_TYPES; i++){
            walkingAnimation.push_back(std::move(
                    AnimatedSprite(sprites.animationSprites[WALKING_TYPE], spawnPoint, i,
                                   ANIMATED_FRAMES, ANIMATED_FRAMES * TIME_PER_IMAGE)));
            shootingAnimation.push_back(std::move(
                    AnimatedSprite(sprites.animationSprites[SHOOTING_TYPE], spawnPoint, i,
                                   ANIMATED_FRAMES, ANIMATED_FRAMES * TIME_PER_IMAGE)));
            dyingAnimation.push_back(std::move(
                    AnimatedSprite(sprites.animationSprites[DYING_TYPE], spawnPoint, i,
                                   ANIMATED_FRAMES, ANIMATED_FRAMES * TIME_PER_IMAGE)));
        }
    }

void EnemyPlayer::walkTo(Vector newPosition) {
    position = newPosition;
    for (int i = 0; i < ENEMY_TYPES; i++){
        walkingAnimation[i].moveTo(newPosition);
        shootingAnimation[i].moveTo(newPosition);
        dyingAnimation[i].moveTo(newPosition);
    }
}

void EnemyPlayer::shoot() {
    if (shootingAnimation[activeWeapon].isAnimating) return;
    shootingAnimation[activeWeapon].isAnimating = true;
    // cambiar animacion activa
}

void EnemyPlayer::changeWeapon(int idWeapon) {
    activeWeapon = idWeapon;
    // cambiar sprites
}
int EnemyPlayer::getActiveWeapon(){
    return activeWeapon;
}
void EnemyPlayer::die() {
    if (dyingAnimation[activeWeapon].isAnimating) return;
    dyingAnimation[activeWeapon].isAnimating = true;
}

void EnemyPlayer::drawFrom(Camera* origin,
                           std::vector<std::vector<int>>& map,
                           SDL_Renderer* renderer,
                           std::vector<double> &wallDistances) {
    shootingAnimation[activeWeapon].drawFrom(origin, map, renderer, wallDistances);
}

int EnemyPlayer::getId() {
    return id;
}

EnemyPlayer::~EnemyPlayer() {}





