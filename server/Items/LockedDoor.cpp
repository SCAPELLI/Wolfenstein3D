

#include "LockedDoor.h"
#include "../Player.h"
LockedDoor::LockedDoor(int id,std::string name, int effect, int uniqueId)
        :  cooldown(0), openTimeLimit(2000),OpenableItem(id, name, effect, uniqueId){}

bool LockedDoor::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    if (player.openDoor()) {
        effect = 1;
        cooldown = openTimeLimit;
        return true;
    }
    return false;
}

void LockedDoor::incrementCooldown() {
    if (effect) {
        cooldown -= 1;
    }
    if (cooldown == 0){
        effect = 0;
    }
}
