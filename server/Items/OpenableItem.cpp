

#include "OpenableItem.h"
#include "unistd.h"
#include "server/include/Player.h"

OpenableItem::OpenableItem(int id,std::string name, int effect,int uniqueId)
:  cooldown(0), openTimeLimit(2000), Item(id, name, effect, uniqueId){}


bool OpenableItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    if (effect == 0 && !cooldown){
        effect = 1;
        cooldown = openTimeLimit;
        return true;
    }
    return false;
}

void OpenableItem::incrementCooldown() {
    if (effect) {
        cooldown -= 1;
    }
    if (cooldown == 0){
        effect = 0;
    }
}