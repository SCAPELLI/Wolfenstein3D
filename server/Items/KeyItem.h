

#ifndef KEYITEM_H
#define KEYITEM_H

#include "../Item.h"
class KeyItem : public Item{
private:

public:
    KeyItem(int id, std::string name, int effect, int uniqueId);
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;


};


#endif //CAMERA_CPP_KEYITEM_H
