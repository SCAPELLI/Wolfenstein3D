#include <vector>
#include "Player.h"


class Map{
    std::vector<int> matrix;
    //Player& player;
public:
    Map();
    Map(std::vector<int> matrix);
    std::vector<int>& getMatrix();
    // void changePosition(Vector& newPos);
    // bool isOkToMove(Vector& newPos);

};
