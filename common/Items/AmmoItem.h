

#ifndef AMMOITEM_H
#define AMMOITEM_H
#include "../Item.h"
#include "AbstractEvent.h"
#include <vector>
class AmmoItem : public Item{
private:
    int id;
    std::string name;
    int effect;
    int uniqueId;
public:
    AmmoItem(int id, std::string name, int quantity, int uniqueId);
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
//    virtual void changeValue(int toChange);
//    virtual int getEffect() ;

};


#endif //AMMOITEM_H
