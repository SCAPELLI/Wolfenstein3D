
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
    Item() : id(-1), effect(0) {};
    Item(int id, int effect);
    int getEffect();
    void changeValue(int toChange);
    //Item(int id, Sprite& newSprite);

    int getItemId();
};


#endif //CPP_ITEM_H
