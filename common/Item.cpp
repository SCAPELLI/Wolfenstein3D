#include "Item.h"
#include "../cliente/Sprite.h"

int Item::uniqueId = 0;

Item::Item(int id,std::string name, int effect)
:  id(id), name(name), effect(effect){
    uniqueId++;
}

int Item::getId(){
    return id;
}
int Item::getEffect() {
    return effect;
}
void Item::changeValue(int toChange){
    effect += toChange;
}

std::string Item::getItemName() {
    return name;
}

int Item::getUniqueId(){
    return uniqueId;
}

bool Item::isConsumed(Player &player) {
    return false;
}
