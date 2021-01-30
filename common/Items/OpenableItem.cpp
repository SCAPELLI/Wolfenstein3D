

#include "OpenableItem.h"

OpenableItem::OpenableItem(int id,std::string name, int effect)
:  id(id), name(name), effect(effect){}

int OpenableItem::getItemId(){
    return id;
}
int OpenableItem::getEffect() {
    return effect;
}
void OpenableItem::changeValue(int toChange){
    effect += toChange;
}