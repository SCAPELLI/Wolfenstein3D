#ifndef WOLF_PLAYERINFO_H
#define WOLF_PLAYERINFO_H

typedef struct PlayerInfo{
    int idPlayer;
    float x;
    float y;
    double angle;
    int life;
    bool isGameOver;
}PlayerInfo;

#endif
