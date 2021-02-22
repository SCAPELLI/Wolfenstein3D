

#ifndef LIFEGAINITEM_H
#define LIFEGAINITEM_H

#include "Item.h"
class LifeGainItem : public Item {
private:
    int id;
    std::string name;
    int effect;
    int uniqueId;
public:
    LifeGainItem(int id,std::string name, int effect, int uniqueId);
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
};


#endif
