#ifndef MAP_H
#define MAP_H
#include "GameLoader.h"
#include <vector>
#include "Player.h"
#include "CellMap.h"


class Map{
    std::vector<std::vector<CellMap>> matrix;
    std::vector<OpenableItem*> doors;
    double width;
    double height;
    GameLoader factory;
public:
    Map(std::vector<Player>& players,
            std::vector<AbstractEvent*>& newEvents);
        Map();
        //Map(std::vector<int> matrix);
        std::vector<std::vector<CellMap>>& getMatrix();
        void changePosition(Vector& newPos, Player& player,
                            std::vector<AbstractEvent*>& newEvents);
        void dropAllItems(Player& player, std::vector<AbstractEvent*>& newEvents);
        bool isOkToMove(Vector& futurePos);
        double getWidth();
        double getHeight();
        void removePlayer(Player& player);
        void addPlayer(Player& player);
        void dropItemPlayer(Player& player, Item itemPlayer);
        void setElemInPosition(int& numOfPlayer, int pos1, int pos2,
                    CellMap& tileMap, std::vector<Player>& players, int elem,
                               std::vector<AbstractEvent*>& newEvents);
        bool isADoor(Player& player, std::vector<AbstractEvent*>& newEvents);
        void increaseCooldown();
    void launchRocket(Rocket* rocket, Vector& direction,
                           std::vector<AbstractEvent*>& newEvents);

};

#endif