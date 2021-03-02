

#include "AmmoItem.h"
#include "server/include/Player.h"

AmmoItem::AmmoItem(int id, std::string name, int quantity, int uniqueId)
: Item(id, name, quantity, uniqueId) {}

bool AmmoItem::isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) {
    return player.getItem(this, newEvents);
}

//Item& operator-=(Item& otherItem){
//
//}
