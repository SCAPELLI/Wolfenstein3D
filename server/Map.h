#ifndef MAP_H
#define MAP_H
#include <vector>
#include "Player.h"
#include "../common/CellMap.h"

//class CellMap;

class Map{
    std::vector<std::vector<CellMap>> matrix;
    std::vector<OpenableItem*> doors;
    double width;
    double height;
    public:
        Map(std::vector<Player>& players,
            std::vector<AbstractEvent*>& newEvents);
        Map();
        //Map(std::vector<int> matrix);
        std::vector<std::vector<CellMap>>& getMatrix();
        void changePosition(Vector& newPos, Player& player,
                            std::vector<AbstractEvent*>& newEvents);
        void dropAllItems(Player& player);
        bool isOkToMove(Vector& futurePos);
        void removePlayer(Player& player);
        void addPlayer(Player& player);
        void dropItemPlayer(Player& player, Item itemPlayer);
        void setElemInPosition(int numOfPlayer, int pos1, int pos2,
                    CellMap& tileMap, std::vector<Player>& players, int elem,
                               std::vector<AbstractEvent*>& newEvents);
        bool isADoor(Player& player, std::vector<AbstractEvent*>& newEvents);
        void increaseCooldown();

};

#endif