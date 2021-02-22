

#ifndef KEYITEM_H
#define KEYITEM_H

#include "Item.h"
class KeyItem : public Item{
private:
    int id;
    std::string name;
    int effect;
    int uniqueId;
public:
    KeyItem(int id, std::string name, int effect, int uniqueId);
    KeyItem();
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
    int getEffect();
    virtual void changeValue(int toChange);
    std::string getItemName();
    int getId();
    int getUniqueId();

};


#endif //CAMERA_CPP_KEYITEM_H
