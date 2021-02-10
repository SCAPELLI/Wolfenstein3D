

#ifndef POINTGAINITEM_H
#define POINTGAINITEM_H

#include "../Item.h"

class PointGainItem : public Item{
    private:
        int id;
        std::string name;
        int effect;
    public:
        PointGainItem(int id, std::string name, int effect);
        PointGainItem();
        bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents)override;
};



#endif
