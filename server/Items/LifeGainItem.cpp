
#include "LifeGainItem.h"
#include "../Player.h"



LifeGainItem::LifeGainItem(int id,std::string name, int effect, int uniqueId)
        :  Item(id, name, effect, uniqueId){}

bool LifeGainItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}