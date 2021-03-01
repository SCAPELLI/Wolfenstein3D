
#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "../common/AbstractEvent.h"
#include <vector>
class Sprite;
class Player;
/* Clase madre que representa un item*/
class Item {
protected:
    int id;
    std::string name;
    int effect;
    int uniqueId;

public:
    Item() : id(-1), name(""), effect(0), uniqueId(0) {};
    Item(int id, std::string name, int effect, int uniqueId);
    virtual int getEffect();
    virtual void changeValue(int toChange);
    virtual std::string getItemName();
    virtual int getId();
    virtual bool isConsumed(Player& player, std::vector<AbstractEvent*>& newEvents);
    int getUniqueId();
    Item& operator-=(Item& otherItem);
    };


#endif //CPP_ITEM_H
