#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H
#include <vector>
#include "Player.h"

class Game {
    public:
    std::vector<std::vector<int>> map;
    std::vector<Player> players;
public:
    Game();
    Game& operator=(Game &&other)noexcept;
    //Game& operator = (const Game& other) = delete;
    Game(const Game& other) = delete;
    void moveAngle(int angle);
    void changePosition(Vector changeTo);
    Vector calculateDirection(int idPlyr);
    void decrementLife();
    Game(Game &&other);
};


#endif //WOLFENSTEIN3D_GAME_H
