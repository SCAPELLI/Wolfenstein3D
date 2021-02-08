#include "PointGainItem.h"
#include "Player.h"

PointGainItem::PointGainItem(int id,std::string name, int effect)
        :  id(id), name(name), effect(effect), Item(id, name, effect){}

PointGainItem::PointGainItem()
: id(1), name(""), effect(0){}

bool PointGainItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}