#include <mutex>
#include "ProtectedEventsQueue.h"
#include "EventsCatcher.h"

//ProtectedEventsQueue::ProtectedEventsQueue() : events(), mutex() {}

void ProtectedEventsQueue::insertEvents(EventsCatcher& eventsCatcher) {
    std::unique_lock<std::mutex> lock(mutex);
    events = std::move(eventsCatcher.getEvents());
}
Event ProtectedEventsQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    Event event = std::move(events.front());
    events.pop();
    return event;
}
bool ProtectedEventsQueue::empty() {
    std::unique_lock<std::mutex> lock(mutex);
    return events.empty();
}
void ProtectedEventsQueue::push(Event& event) {
    std::unique_lock<std::mutex> lock(mutex);
    events.push(std::move(event));
}
