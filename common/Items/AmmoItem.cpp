

#include "AmmoItem.h"
#include "GameLoader.h"

AmmoItem::AmmoItem()
{
    GameLoader yaml;
    name = "ammo";
    yaml.configItem(id, name, quantity);
}

AmmoItem::AmmoItem(int id, std::string name, int quantity)
: id(id), name(name), quantity(quantity) {}