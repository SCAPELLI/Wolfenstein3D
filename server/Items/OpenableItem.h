

#ifndef OPENABLEITEM_H
#define OPENABLEITEM_H
#include "../Item.h"

class OpenableItem : public Item {
private:
    int cooldown;
    int openTimeLimit;
public:
    OpenableItem(int id,std::string name, int effect, int uniqueId);
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
    virtual void incrementCooldown();
//    virtual int getEffect();
};

#endif //OPENABLEITEM_H
