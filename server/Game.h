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
    AbstractEvent newChanges;
public:
    Game();
    Game(const Game& other) = delete;
    int generateRandom();
    void moveAngle(double angle, int idPlayer);
    void changePosition(Vector changeTo, int idPlayer,
                                 std::vector<AbstractEvent*>& newEvents);
    Vector calculateDirection(int idPlyr);
    int getDamage(int idPlyr);
    int shoot(int idPlayer);
    void decrementLife(int idPlyr);
    bool openTheDoor(int idPlayer, std::vector<AbstractEvent*>& newEvents);
    void increaseCooldown();

};


#endif //WOLFENSTEIN3D_GAME_H
