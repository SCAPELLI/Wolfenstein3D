

#ifndef LOCKEDDOOR_H
#define LOCKEDDOOR_H
#include "OpenableItem.h"

class LockedDoor: public OpenableItem {
private:
    int id;
    std::string name;
    int effect;
    int uniqueId;
    int openTimeLimit;
    int cooldown;
public:
    LockedDoor(int id,std::string name, int effect, int uniqueId);
    bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents) override;
    void incrementCooldown();
};

#endif //LOCKEDDOOR_H
