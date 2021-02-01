#include "PointGainItem.h"
#include "Player.h"

PointGainItem::PointGainItem(int id,std::string name, int effect)
        :  id(id), name(name), effect(effect){}

PointGainItem::PointGainItem()
: id(1), name(""), effect(0){}

bool PointGainItem::isConsumed(Player &player) {
    return player.getItem(this);
}