#ifndef BLOCKEDEVENTQUEUE_H
#define BLOCKEDEVENTQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Event.h"
class EventsCatcher;

class BlockingEventsQueue {
    std::queue<Event> events{};
    std::mutex mutex{};
    std::condition_variable cv;
public:
    BlockingEventsQueue();
    void insertEvents(EventsCatcher& eventsCatcher);
    Event pop();
    bool empty();
    void push(Event& event);
};

#endif