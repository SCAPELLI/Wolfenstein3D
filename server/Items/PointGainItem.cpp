#include "PointGainItem.h"
#include "server/include/Player.h"

PointGainItem::PointGainItem(int id,std::string name, int effect, int uniqueId)
        : Item(id, name, effect, uniqueId){}

//PointGainItem::PointGainItem()
//: id(1), name(""), effect(0){}

bool PointGainItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}


//void PointGainItem::changeValue(int value) {
//    effect += value;
//}

PointGainItem::~PointGainItem() {}