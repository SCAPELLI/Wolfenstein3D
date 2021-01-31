

#ifndef AMMOITEM_H
#define AMMOITEM_H
#include "../Item.h"

class AmmoItem : public Item{
private:
    int id;
    std::string name;
    int quantity;
public:
    AmmoItem();
    AmmoItem(int id, std::string name, int quantity);

};


#endif //AMMOITEM_H
