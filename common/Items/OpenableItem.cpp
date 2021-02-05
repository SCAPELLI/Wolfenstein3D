

#include "OpenableItem.h"
#include "unistd.h"

OpenableItem::OpenableItem(int id,std::string name, int effect)
:  id(id), name(name), effect(effect), Item(id, name, effect){}


bool OpenableItem::isConsumed(Player &player) {
    if (getEffect() == 0){
        effect = 1;
        return true;
    }
    return false;
}

void OpenableItem::incrementCooldown() {
    if (effect) {
        cooldown += 1;
        cooldown %= openTimeLimit;
    }
    if (cooldown == 0){
        effect =-1;
    }
}