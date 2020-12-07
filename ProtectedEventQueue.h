#ifndef PROTECTEDEVENTQUEUE_H
#define PROTECTEDEVENTQUEUE_H

#include <queue>
#include <mutex>

class Event;
class EventsCatcher;

class ProtectedEventQueue {
    std::queue<Event> events{};
    std::mutex mutex{};
public:
    void insertEvents(EventsCatcher& eventsCatcher);
    Event pop();
    bool empty();
};

#endif
