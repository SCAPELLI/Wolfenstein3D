

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
    int getItemId();
    int getEffect();
    void changeValue(int toChange);
};

#endif //LOCKEDDOOR_H
