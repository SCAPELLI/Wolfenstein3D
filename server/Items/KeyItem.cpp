#include "KeyItem.h"

#include "../Player.h"

KeyItem::KeyItem(int id,std::string name, int effect, int uniqueId)
        :
        Item(id, name, effect, uniqueId){}

bool KeyItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}
//int KeyItem::getEffect(){
//    return effect;
//}
//void KeyItem::changeValue(int toChange){
//    effect += toChange;
//}
//
//std::string KeyItem::getItemName(){
//    return name;
//}
//int KeyItem::getId(){
//    return id;
//}
//int KeyItem::getUniqueId(){
//    return uniqueId;
//}
//Item& operator-=(Item& otherItem);