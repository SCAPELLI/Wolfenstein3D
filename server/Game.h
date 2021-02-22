#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H
#include <vector>
#include "Player.h"
#include "Map.h"
#include "AbstractEvent.h"

class Game {
    public:
    int levelId;
    int speed;
    Map map;
    std::map<int, int> ids;
    std::vector<Player> players;
    //AbstractEvent newChanges;
public:
    Game();
    Game(std::vector<AbstractEvent*>& newEvents,
         std::map<int, std::string>& playersNames, int levelId);
    Game(const Game& other) = default;
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
    void respawnPlayer(int idPlayer, std::vector<AbstractEvent*>& newEvents);

};


#endif //WOLFENSTEIN3D_GAME_H
