#include <mutex>
#include "ProtectedEventQueue.h"
#include "EventsCatcher.h"

void ProtectedEventQueue::insertEvents(EventsCatcher& eventsCatcher) {
    std::lock_guard<std::mutex> lock(mutex);
    events = std::move(eventsCatcher.getEvents());
}
Event ProtectedEventQueue::pop() {
    std::lock_guard<std::mutex> lock(mutex);
    Event event = std::move(events.front());
    events.pop();
    return event;
}
bool ProtectedEventQueue::empty() {
    std::lock_guard<std::mutex> lock(mutex);
    return events.empty();
}