
#ifndef WOLF_ENEMYPLAYER_H
#define WOLF_ENEMYPLAYER_H
#include "AnimatedSprite.h"
#include "Vector.h"

class EnemyPlayer {

    SDL_Renderer* renderer;
    int activeWeapon, id;
    Vector position, spawnPoint;
    AnimatedSprite walkingAnimation, dyingAnimation, shootingAnimation;

    public:
        EnemyPlayer(SDL_Renderer* renderer, int id, Vector spawnPoint);
        void walkTo(Vector newPosition);
        void shoot();
        void changeWeapon(int idWeapon);
        void die();
        void draw(std::vector<double> &wallDistances);
        int getId();
        ~EnemyPlayer();
};


#endif //WOLF_ENEMYPLAYER_H
