#include <mutex>
#include "communications/common/include/ProtectedEventsQueue.h"
#include "EventsCatcher.h"

void ProtectedEventsQueue::insertEvents(EventsCatcher& eventsCatcher) {
    std::lock_guard<std::mutex> lock(mutex);
    events = std::move(eventsCatcher.getEvents());
}
Event ProtectedEventsQueue::pop() {
    std::lock_guard<std::mutex> lock(mutex);
    Event event = std::move(events.front());
    events.pop();
    return event;
}
bool ProtectedEventsQueue::empty() {
    std::lock_guard<std::mutex> lock(mutex);
    return events.empty();
}
void ProtectedEventsQueue::push(Event& event) {
    std::lock_guard<std::mutex> lock(mutex);
    events.push(std::move(event));
}
