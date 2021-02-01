
#include "LifeGainItem.h"
#include "../../server/Player.h"


//Item::Item(int id, Sprite &newSprite)
//:    id(id), sprite(newSprite)
//{}
LifeGainItem::LifeGainItem(int id,std::string name, int effect)
        :  id(id), name(name), effect(effect), Item(id, name, effect){}

bool LifeGainItem::isConsumed(Player &player) {
    return player.getItem(this);
}