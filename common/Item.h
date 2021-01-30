
#ifndef ITEM_H
#define ITEM_H
#include <string>

class Sprite;

class Item {
    int id;
    std::string name;
    int effect;
    //Sprite& sprite;

public:
    Item() : id(-1), name(""), effect(0) {};
    Item(int id, std::string name, int effect);
    int getEffect();
    void changeValue(int toChange);
    std::string getItemName();
    int getItemId();
};


#endif //CPP_ITEM_H
