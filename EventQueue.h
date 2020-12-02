#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <queue>
#include "Event.h"

class EventQueue {
public:
    std::queue<Event> getEvents();
};

#endif
