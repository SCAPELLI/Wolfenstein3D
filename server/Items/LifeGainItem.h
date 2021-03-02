

#ifndef LIFEGAINITEM_H
#define LIFEGAINITEM_H

#include "server/include/Item.h"
class LifeGainItem : public Item {

public:
    LifeGainItem(int id,std::string name, int effect, int uniqueId);
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
};


#endif
