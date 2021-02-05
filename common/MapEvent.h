

#ifndef CAMERA_CPP_MAPEVENT_H
#define CAMERA_CPP_MAPEVENT_H
#include "Item.h"
#include "AbstractEvent.h"
#include <map>

class MapEvent : public AbstractEvent{
    std::map<int, AbstractEvent*> events;
public:
    MapEvent();
    void addItem(Item* item, int x, int y);
    void removeItem(Item* item);

};


#endif //CAMERA_CPP_MAPEVENT_H
