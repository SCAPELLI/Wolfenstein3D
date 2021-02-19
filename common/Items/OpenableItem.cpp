

#include "OpenableItem.h"
#include "unistd.h"
#include "Player.h"

OpenableItem::OpenableItem(int id,std::string name, int effect,int uniqueId)
:  id(id), name(name), effect(effect), uniqueId(uniqueId),
    cooldown(0), Item(id, name, effect, uniqueId){}


bool OpenableItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
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