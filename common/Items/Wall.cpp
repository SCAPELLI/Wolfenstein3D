

#include "Wall.h"

Wall::Wall(int id,std::string name, int effect)
        :  id(id), name(name), effect(effect), Item(id, name, effect){}
