#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <queue>
#include "Event.h"

class EventsCatcher {
public:
    std::queue<Event> getEvents();
};

#endif
