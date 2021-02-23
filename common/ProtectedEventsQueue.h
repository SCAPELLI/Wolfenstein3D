#ifndef PROTECTEDEVENTQUEUE_H
#define PROTECTEDEVENTQUEUE_H

#include <queue>
#include <mutex>

#include "Event.h"
class EventsCatcher;
/* Cola protegida para encolar los eventos*/
class ProtectedEventsQueue {
    std::queue<Event> events;
    std::mutex mutex;
public:
//    ProtectedEventsQueue();
    void insertEvents(EventsCatcher& eventsCatcher);
    Event pop();
    bool empty();
    void push(Event& event);
};

#endif
