

#ifndef LIFEGAINITEM_H
#define LIFEGAINITEM_H

#include "../Item.h"
class LifeGainItem : public Item {
private:
    int id;
    std::string name;
    int effect;
public:
    LifeGainItem(int id,std::string name, int effect);
    bool isConsumed(Player& player) override;
};


#endif
