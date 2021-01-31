

#ifndef KEYITEM_H
#define KEYITEM_H

#include "../Item.h"
class KeyItem : public Item{
private:
    int id;
    std::string name;
    int effect;
public:
    KeyItem(int id, std::string name, int effect);
    KeyItem();
};


#endif //CAMERA_CPP_KEYITEM_H
