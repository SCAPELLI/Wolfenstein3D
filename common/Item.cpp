#include "Item.h"
#include "../cliente/Sprite.h"

//Item::Item(int id, Sprite &newSprite)
//:    id(id), sprite(newSprite)
//{}
Item::Item(int id,std::string name, int effect)
:  id(id), name(name), effect(effect){}

int Item::getItemId(){
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

Item* Item::getInstance(){
    return this;
}

bool Item::isConsumed(Player &player) {
    return false;
}
