#include <mutex>
#include "BlockingEventsQueue.h"
#include "EventsCatcher.h"
BlockingEventsQueue::BlockingEventsQueue() : events(), mutex(), cv(){}

void BlockingEventsQueue::insertEvents(EventsCatcher& eventsCatcher) {
    std::unique_lock<std::mutex> lock(mutex);
    events = std::move(eventsCatcher.getEvents());
}
Event BlockingEventsQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    while (events.empty()) {
        cv.wait(lock);
    }
    Event event = std::move(events.front());
    events.pop();
    return event;
}
bool BlockingEventsQueue::empty() {
    std::unique_lock<std::mutex> lock(mutex);
    return events.empty();
}
void BlockingEventsQueue::push(Event& event) {
    std::unique_lock<std::mutex> lock(mutex);
    events.push(std::move(event));
    cv.notify_all();
}
