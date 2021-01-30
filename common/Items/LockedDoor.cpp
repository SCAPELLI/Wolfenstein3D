

#include "LockedDoor.h"
LockedDoor::LockedDoor(int id,std::string name, int effect)
        :  id(id), name(name), effect(effect){}

int LockedDoor::getItemId(){
    return id;
}
int LockedDoor::getEffect() {
    return effect;
}
void LockedDoor::changeValue(int toChange){
    effect += toChange;
}