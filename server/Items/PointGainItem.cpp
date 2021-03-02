#include "PointGainItem.h"
#include "server/include/Player.h"

PointGainItem::PointGainItem(int id,std::string name, int effect, int uniqueId)
        : Item(id, name, effect, uniqueId){}


bool PointGainItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}

PointGainItem::~PointGainItem() {}