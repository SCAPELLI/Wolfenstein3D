

#include "AmmoItem.h"
#include "Player.h"

//AmmoItem::AmmoItem()
//{
//    GameLoader yaml;
//    name = "ammo";
//    yaml.configItem(id, name, effect);
//}

AmmoItem::AmmoItem(int id, std::string name, int quantity, int uniqueId)
: id(id), name(name), effect(quantity), uniqueId(uniqueId), Item(id, name, quantity, uniqueId) {}

bool AmmoItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}

