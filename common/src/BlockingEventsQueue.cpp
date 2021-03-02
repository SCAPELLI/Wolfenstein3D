#include <mutex>
#include "common/include/BlockingEventsQueue.h"
#include "common/include/EventsCatcher.h"
BlockingEventsQueue::BlockingEventsQueue() : events(), mutex(), cv(){}

Message BlockingEventsQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    while (events.empty()) {
        cv.wait(lock);
    }
    Message msg = std::move(events.front());
    events.pop();
    return msg;
}
bool BlockingEventsQueue::empty() {
    std::unique_lock<std::mutex> lock(mutex);
    return events.empty();
}
void BlockingEventsQueue::push(Message msg) {
    std::unique_lock<std::mutex> lock(mutex);
    events.push(std::move(msg));
    cv.notify_all();
}
