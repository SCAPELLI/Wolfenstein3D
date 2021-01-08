#include "Item.h"
#include "../cliente/Sprite.h"

//Item::Item(int id, Sprite &newSprite)
//:    id(id), sprite(newSprite)
//{}
Item::Item(int id, int effect) :  id(id), effect(effect){}

int Item::getItemId(){
    return id;
}
int Item::getEffect() {
    return effect;
}
void Item::changeValue(int toChange){
    effect += toChange;
}