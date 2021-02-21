

#ifndef OPENABLEITEM_H
#define OPENABLEITEM_H
#include "../Item.h"

class OpenableItem : public Item {
private:
    int id;
    std::string name;
    int effect;
    int uniqueId;
    int cooldown;
    int openTimeLimit;
public:
    OpenableItem(int id,std::string name, int effect, int uniqueId);
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
    void incrementCooldown();
    int getEffect();
};

#endif //OPENABLEITEM_H
