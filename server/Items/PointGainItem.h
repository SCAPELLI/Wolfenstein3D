

#ifndef POINTGAINITEM_H
#define POINTGAINITEM_H

#include "../Item.h"

class PointGainItem : public Item{

    public:
        PointGainItem(int id, std::string name, int effect, int uniqueId);
        virtual bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents)override;
        //virtual void changeValue(int value);
        ~PointGainItem();
};



#endif
