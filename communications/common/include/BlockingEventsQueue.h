#ifndef BLOCKEDEVENTQUEUE_H
#define BLOCKEDEVENTQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

class Event;
class EventsCatcher;

class BlockingEventsQueue {
    std::queue<Event> events{};
    std::mutex mutex{};
    std::condition_variable cv;
public:
    void insertEvents(EventsCatcher& eventsCatcher);
    Event pop();
    bool empty();
    void push(Event& event);
};

#endif
