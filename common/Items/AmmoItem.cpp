

#include "AmmoItem.h"
#include "GameLoader.h"

AmmoItem::AmmoItem()
{
    GameLoader yaml;
    name = "ammo";
    yaml.configItem(id, name, effect);
}

AmmoItem::AmmoItem(int id, std::string name, int quantity)
: id(id), name(name), effect(quantity), Item(id, name, quantity) {}

bool AmmoItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}

