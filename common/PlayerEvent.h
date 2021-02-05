

#ifndef PLAYEREVENT_H
#define PLAYEREVENT_H

#include "AbstractEvent.h"
#include <map>
#include "Item.h"

class PlayerEvent : public AbstractEvent{
    std::map<int, AbstractEvent*> events;
public:
    PlayerEvent();
    void addItem(Player* player, int x, int y);
    void addItem(Player* player);
    void removeItem(Player* player);

};


#endif //PLAYEREVENT_H
