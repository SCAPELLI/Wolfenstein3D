#ifndef BLOCKEDEVENTQUEUE_H
#define BLOCKEDEVENTQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "Message.h"
#include "Event.h"

/* Cola de eventos usada para encolar eventos a los usuarios*/
class BlockingEventsQueue {
    std::queue<Message> events{};
    std::mutex mutex{};
    std::condition_variable cv;
public:
    BlockingEventsQueue();
    Message pop();
    bool empty();
    void push(Message event);
};

#endif
