

#ifndef OPENABLEITEM_H
#define OPENABLEITEM_H
#include "../Item.h"

class OpenableItem : public Item {
private:
    int id;
    std::string name;
    int effect;
public:
    OpenableItem(int id,std::string name, int effect);
    int getItemId();
    int getEffect();
    void changeValue(int toChange);
};

#endif //OPENABLEITEM_H
