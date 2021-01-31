

#ifndef LOCKEDDOOR_H
#define LOCKEDDOOR_H
#include "../Item.h"

class LockedDoor: public Item {
private:
    int id;
    std::string name;
    int effect;
public:
    LockedDoor(int id,std::string name, int effect);

};

#endif //LOCKEDDOOR_H
