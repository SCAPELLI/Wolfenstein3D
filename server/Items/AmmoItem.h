

#ifndef AMMOITEM_H
#define AMMOITEM_H
#include "server/include/Item.h"
#include "common/include/AbstractEvent.h"
#include <vector>
class AmmoItem : public Item{
private:

public:
    AmmoItem(int id, std::string name, int quantity, int uniqueId);
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
    Item& operator-=(AmmoItem& otherItem);
//    virtual void changeValue(int toChange);
//    virtual int getEffect() ;

};


#endif //AMMOITEM_H
