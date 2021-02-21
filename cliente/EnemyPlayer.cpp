//
// Created by juankristal on 20/2/21.
//

#include "EnemyPlayer.h"
#define WALK_PATH "../cliente/sprites/enemy_sprites/walking/1-"
#define SHOOT_PATH "../cliente/sprites/enemy_sprites/shooting/1-"
#define DYING_PATH "../cliente/sprites/enemy_sprites/dying/1-"
#define TIME_PER_IMAGE 5
#define ANIMATED_FRAMES_WALK 5
#define ANIMATED_FRAMES_SHOOT 3
#define ANIMATED_FRAMES_DEAD 4

EnemyPlayer::EnemyPlayer(SDL_Renderer *renderer, int id, Vector spawnPoint):
    renderer(renderer), activeWeapon(1), id(id), position(spawnPoint), spawnPoint(spawnPoint), // active animation
    walkingAnimation(WALK_PATH, renderer, ANIMATED_FRAMES_WALK, ANIMATED_FRAMES_WALK * TIME_PER_IMAGE),
    dyingAnimation(DYING_PATH, renderer, ANIMATED_FRAMES_SHOOT, ANIMATED_FRAMES_SHOOT * TIME_PER_IMAGE),
    shootingAnimation(SHOOT_PATH, renderer, ANIMATED_FRAMES_DEAD, ANIMATED_FRAMES_DEAD * TIME_PER_IMAGE){}

void EnemyPlayer::walkTo(Vector newPosition) {
    position = newPosition;
}

void EnemyPlayer::shoot() {
    if (shootingAnimation.isAnimating) return ;
    shootingAnimation.isAnimating = true;
    // cambiar animacion activa
}

void EnemyPlayer::changeWeapon(int idWeapon) {
    activeWeapon = idWeapon;
    // cambiar sprites
}

void EnemyPlayer::die() {
    if (dyingAnimation.isAnimating) return;
    dyingAnimation.isAnimating = true;
}

void EnemyPlayer::draw(std::vector<double> &wallDistances) {
    shootingAnimation.rayCast(renderer, position.y, position.x,wallDistances);
}

int EnemyPlayer::getId() {
    return id;
}

EnemyPlayer::~EnemyPlayer() {}





