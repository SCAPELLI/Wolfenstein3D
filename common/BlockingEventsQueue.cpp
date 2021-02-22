#include <mutex>
#include "BlockingEventsQueue.h"
#include "EventsCatcher.h"

void BlockingEventsQueue::insertEvents(EventsCatcher& eventsCatcher) {
    std::lock_guard<std::mutex> lock(mutex);
    events = std::move(eventsCatcher.getEvents());
}
Event BlockingEventsQueue::pop() {
    std::lock_guard<std::mutex> lock(mutex);
    while (events.empty()) {
        cv.wait(lock);
    }
    Event event = std::move(events.front());
    events.pop();
    return event;
}
bool BlockingEventsQueue::empty() {
    std::lock_guard<std::mutex> lock(mutex);
    return events.empty();
}
void BlockingEventsQueue::push(Event& event) {
    std::lock_guard<std::mutex> lock(mutex);
    events.push(std::move(event));
    cv.notify_all();
}
