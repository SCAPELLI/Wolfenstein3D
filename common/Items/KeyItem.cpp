#include "KeyItem.h"

KeyItem::KeyItem(int id,std::string name, int effect)
        :  id(id), name(name), effect(effect){}

KeyItem::KeyItem()
: id(2), name("key"), effect(0){}
int KeyItem::getItemId(){
    return id;
}
int KeyItem::getEffect() {
    return effect;
}
void KeyItem::changeValue(int toChange){
    effect += toChange;
}