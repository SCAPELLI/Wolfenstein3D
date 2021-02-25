#ifndef MAP_H
#define MAP_H
#include "GameLoader.h"
#include <vector>
#include "Player.h"
#include "CellMap.h"

/* matriz que representa el mapa y en cada posicion contiene una CellMap*/
class Map{
    std::vector<std::vector<CellMap>> matrix;
    std::vector<OpenableItem*> doors;
    double width;
    double height;
    GameLoader factory;
public:
    Map(std::vector<Player>& players,
            std::vector<AbstractEvent*>& newEvents, int levelId);
        Map();
        void changePosition(Vector& newPos, Player& player,
                            std::vector<AbstractEvent*>& newEvents);
        void dropAllItems(Player& player, std::vector<AbstractEvent*>& newEvents);
        bool isOkToMove(Vector& futurePos);
        double getWidth();
        double getHeight();
        void setElemInPosition(int& numOfPlayer, int pos1, int pos2,
                    CellMap& tileMap, std::vector<Player>& players, int elem,
                               std::vector<AbstractEvent*>& newEvents);
        bool isADoor(Player& player, std::vector<AbstractEvent*>& newEvents);
        void increaseCooldown();
        void launchRocket(Rocket* rocket, Vector& direction,
                           std::vector<AbstractEvent*>& newEvents);

};

#endif