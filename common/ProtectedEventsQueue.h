#ifndef PROTECTEDEVENTQUEUE_H
#define PROTECTEDEVENTQUEUE_H

#include <queue>
#include <mutex>

#include "Event.h"
class EventsCatcher;

class ProtectedEventsQueue {
    std::queue<Event> events;
    std::mutex mutex;
public:
    void insertEvents(EventsCatcher& eventsCatcher);
    Event pop();
    bool empty();
    void push(Event& event);
};

#endif
