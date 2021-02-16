#include "Item.h"
#include "../cliente/Sprite.h"


Item::Item(int id,std::string name, int effect, int uniqueId)
:  id(id), name(name), effect(effect), uniqueId(uniqueId){

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

bool Item::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return false;
}

Item& Item::operator-=(Item& otherItem) {
    if (this->effect - otherItem.effect >= 0)
        this->effect -= otherItem.effect;
    return *this;
}