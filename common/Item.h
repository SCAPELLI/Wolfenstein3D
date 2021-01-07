
#ifndef ITEM_H
#define ITEM_H

class Sprite;

class Item {
int id;
Sprite& sprite;

public:
    Item(int id, Sprite& newSprite);

    int getItemId();
};


#endif //CPP_ITEM_H
