#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H
#include <vector>
#include "Player.h"

class Game {
    public:
    std::vector<std::vector<int>> map;
    std::vector<Player> players;
    int speed;
public:
    Game();
    Game(const Game& other) = delete;
    void moveAngle(double angle, int idPlayer);
    void changePosition(Vector changeTo);
    Vector calculateDirection(int idPlyr);
    int getDamage(int idPlyr);
    int shoot(int idPlayer, int idWeapon, Vector& direction);
    void decrementLife(int idPlyr);

};


#endif //WOLFENSTEIN3D_GAME_H
