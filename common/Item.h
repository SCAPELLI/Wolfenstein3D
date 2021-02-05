
#ifndef ITEM_H
#define ITEM_H
#include <string>

class Sprite;
class Player;

class Item {
    int id;
    std::string name;
    int effect;
    static int uniqueId;

public:
    Item() : id(-1), name(""), effect(0) {};
    Item(int id, std::string name, int effect);
    int getEffect();
    void changeValue(int toChange);
    std::string getItemName();
    int getId();
    virtual bool isConsumed(Player& player);
    int getUniqueId();
    };


#endif //CPP_ITEM_H
