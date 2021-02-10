

#ifndef OPENABLEITEM_H
#define OPENABLEITEM_H
#include "../Item.h"

class OpenableItem : public Item {
private:
    int id;
    std::string name;
    int effect;
    int openTimeLimit;
    int cooldown;
public:
    OpenableItem(int id,std::string name, int effect);
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
    void incrementCooldown();

};

#endif //OPENABLEITEM_H
