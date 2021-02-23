
#include "LifeGainItem.h"
#include "server/Player.h"


//Item::Item(int id, Sprite &newSprite)
//:    id(id), sprite(newSprite)
//{}
LifeGainItem::LifeGainItem(int id,std::string name, int effect, int uniqueId)
        :  id(id), name(name), effect(effect), uniqueId(uniqueId), Item(id, name, effect, uniqueId){}

bool LifeGainItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}