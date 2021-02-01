

#include "AmmoItem.h"
#include "GameLoader.h"

AmmoItem::AmmoItem()
{
    GameLoader yaml;
    name = "ammo";
    yaml.configItem(id, name, effect);
}

AmmoItem::AmmoItem(int id, std::string name, int quantity)
: id(id), name(name), effect(quantity) {}

bool AmmoItem::isConsumed(Player &player) {
    return player.getItem(this);
}

void AmmoItem::changeValue(int toChange) {
    effect += toChange;
}

int AmmoItem::getEffect() {
    return effect;
}