#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <queue>
#include "Event.h"

class EventsCatcher {
    int playerId;
public:
    EventsCatcher(int playerId);
    std::queue<Event> getEvents();
    ~EventsCatcher() = default;
};

#endif
