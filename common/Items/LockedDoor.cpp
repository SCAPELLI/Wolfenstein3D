

#include "LockedDoor.h"
#include "Player.h"
LockedDoor::LockedDoor(int id,std::string name, int effect)
        :  id(id), name(name), effect(effect), Item(id, name, effect){}

bool LockedDoor::isConsumed(Player &player) {
    if (player.openDoor()) changeValue(1);
    return false;
}