#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H
#include <vector>
#include "Player.h"
#include "Map.h"
#include "common/include/AbstractEvent.h"
/* Lógica donde se ejecuta el juego*/
class Game {
    public:
    int levelId;
    Map map;
    std::map<int, int> ids;
    std::vector<Player> players;
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
    int shoot(int idPlayer, std::vector<AbstractEvent*>& newEvents);
    bool openTheDoor(int idPlayer, std::vector<AbstractEvent*>& newEvents);
    void getHighscores(std::map<std::string, std::vector<int>>& names);
    void increaseCooldown();
    bool canShoot(int idPlayer, int otherPlayer);
    void respawnPlayer(int idPlayer, std::vector<AbstractEvent*>& newEvents);
    void reactToDamage(int damaged, int sender,std::vector<AbstractEvent*>& newEvents);
    int getBullets(int idPlayer);
    bool GameFinished();
    int getWinnerId();
    };


#endif //WOLFENSTEIN3D_GAME_H
