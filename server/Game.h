#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H
#include <vector>
#include "Player.h"
#include "Map.h"
#include "AbstractEvent.h"


class Game {
    public:
    int speed;
    Map map;
    std::vector<Player> players;
    //AbstractEvent newChanges;
public:
    Game();
    Game(std::vector<AbstractEvent*>& newEvents,
         std::vector<std::string>& playersNames);
    Game(const Game& other) = default;
    int generateRandom();
    void moveAngle(double angle, int idPlayer);
    void changePosition(Vector changeTo, int idPlayer,
                                 std::vector<AbstractEvent*>& newEvents);
    Vector calculateDirection(int idPlyr);
    bool changeWeapon(int idPlayer, int idWeapon);
    int getDamage(int idPlyr);
    int shoot(int idPlayer, std::vector<AbstractEvent*>& newEvents);
    //void decrementLife(int idPlyr);
    bool openTheDoor(int idPlayer, std::vector<AbstractEvent*>& newEvents);
    void increaseCooldown();
    bool canShoot(int idPlayer, int otherPlayer);
    void respawnPlayer(int idPlayer);

};


#endif //WOLFENSTEIN3D_GAME_H
