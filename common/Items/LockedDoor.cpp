

#include "LockedDoor.h"
#include "Player.h"
LockedDoor::LockedDoor(int id,std::string name, int effect, int uniqueId)
        :  id(id), name(name), effect(effect), uniqueId(uniqueId), OpenableItem(id, name, effect, uniqueId){}

bool LockedDoor::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    if (player.openDoor()) changeValue(1);
    return false;
}