

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
};

#endif //OPENABLEITEM_H
