#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H
#include <vector>
#include "Player.h"
#include "Map.h"

class Game {
    public:
    int speed;
    Map map;
    std::vector<Player> players;
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
