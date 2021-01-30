
#include "LifeGainItem.h"



//Item::Item(int id, Sprite &newSprite)
//:    id(id), sprite(newSprite)
//{}
LifeGainItem::LifeGainItem(int id,std::string name, int effect)
        :  id(id), name(name), effect(effect){}

int LifeGainItem::getItemId(){
    return id;
}
int LifeGainItem::getEffect() {
    return effect;
}
void LifeGainItem::changeValue(int toChange){
    effect += toChange;
}