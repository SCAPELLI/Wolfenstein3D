

#ifndef CAMERA_CPP_WALL_H
#define CAMERA_CPP_WALL_H

#include "../Item.h"

class ItemWall : public Item{
private:
    int id;
    std::string name;
    int effect;

public:
    ItemWall(int id,std::string name, int effect);
};


#endif //CAMERA_CPP_WALL_H
