
#ifndef WOLF_ENEMYPLAYER_H
#define WOLF_ENEMYPLAYER_H
#include "AnimatedSprite.h"
#include "Vector.h"
#include "BagOfSprites.h"

class EnemyPlayer {

    SDL_Renderer* renderer;
    int activeWeapon, id;
    Vector position, spawnPoint;
    std::vector<AnimatedSprite> walkingAnimation, dyingAnimation, shootingAnimation;

    public:
        EnemyPlayer(SDL_Renderer* renderer, int id, Vector spawnPoint, BagOfSprites& sprites);
        void walkTo(Vector newPosition);
        void shoot();
        void changeWeapon(int idWeapon);
        void die();
        void drawFrom(Camera* origin,
                      std::vector<std::vector<int>>& map,
                      SDL_Renderer* renderer,
                      std::vector<double> &wallDistances);
        int getId();
        ~EnemyPlayer();
};


#endif //WOLF_ENEMYPLAYER_H
