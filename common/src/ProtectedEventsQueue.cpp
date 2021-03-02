#include <mutex>
#include "common/include/ProtectedEventsQueue.h"
#include "common/include/Message.h"

std::list<Message> ProtectedEventsQueue::popAll() {
    std::unique_lock<std::mutex> lock(mutex);

    std::list<Message> eventsToPop;
    while (!events.empty()) {
        eventsToPop.push_back(events.front());
        events.pop_front();
    }
    return eventsToPop;
}
bool ProtectedEventsQueue::empty() {
    std::unique_lock<std::mutex> lock(mutex);
    return events.empty();
}
void ProtectedEventsQueue::push(Message& eventToPush) {
    std::unique_lock<std::mutex> lock(mutex);
    events.push_back(eventToPush);
}
