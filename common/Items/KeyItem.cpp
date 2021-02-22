#include "KeyItem.h"

#include "Player.h"

KeyItem::KeyItem(int id,std::string name, int effect, int uniqueId)
        :  id(id), name(name), effect(effect), uniqueId(uniqueId),
        Item(id, name, effect, uniqueId){}

//KeyItem::KeyItem(){
//    GameLoader yaml;
//    name = "key";
//    yaml.configItem(id, name, effect);
//}

bool KeyItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}
int KeyItem::getEffect(){
    return effect;
}
void KeyItem::changeValue(int toChange){
    effect += toChange;
}

std::string KeyItem::getItemName(){
    return name;
}
int KeyItem::getId(){
    return id;
}
int KeyItem::getUniqueId(){
    return uniqueId;
}
//Item& operator-=(Item& otherItem);