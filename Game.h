#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H
#include <vector>
#include "Player.h"

class Game {
    public:
    std::vector<std::vector<int>> map;
    Player player;
public:
    Game(std::vector<std::vector<int>> map, Player player);
    Game& operator=(Game &&other)noexcept;
    //Game& operator = (const Game& other) = delete;
    Game(const Game& other) = delete;
    void moveAngle(int angle);
    void changePosition(int dx, int dy);
    void decrementLife();
    Game(Game &&other);
};


#endif //WOLFENSTEIN3D_GAME_H
