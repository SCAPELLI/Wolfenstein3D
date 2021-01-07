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
    int generateRandom();
    void moveAngle(double angle, int idPlayer);
    void changePosition(Vector changeTo, int idPlayer);
    Vector calculateDirection(int idPlyr);
    int getDamage(int idPlyr);
    int shoot(int idPlayer);
    void decrementLife(int idPlyr);
    bool openTheDoor(int idPlayer);

};


#endif //WOLFENSTEIN3D_GAME_H
