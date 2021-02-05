#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H
#include <vector>
#include "Player.h"
#include "Map.h"
#include "AbstractEvent.h"
#include "PlayerEvent.h"

class Game {
    public:
    int speed;
    Map map;
    std::vector<Player> players;
    PlayerEvent playerEvent;
public:
    Game();
    Game(const Game& other) = delete;
    int generateRandom();
    void moveAngle(double angle, int idPlayer);
    AbstractEvent changePosition(Vector changeTo, int idPlayer);
    Vector calculateDirection(int idPlyr);
    int getDamage(int idPlyr);
    int shoot(int idPlayer);
    void decrementLife(int idPlyr);
    bool openTheDoor(int idPlayer);
    void increaseCooldown();

};


#endif //WOLFENSTEIN3D_GAME_H
