#ifndef MAP_H
#define MAP_H
#include <vector>
#include "Player.h"
#include "../common/CellMap.h"
//class CellMap;

class Map{
    std::vector<std::vector<CellMap>> matrix;
    //Player& player;
    public:
        Map();
        //Map(std::vector<int> matrix);
        std::vector<std::vector<CellMap>>& getMatrix();
         void changePosition(Vector newPos, Vector oldPos);
         bool isOkToMove(Vector& newPos);

};

#endif