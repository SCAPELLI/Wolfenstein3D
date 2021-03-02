#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <queue>
#include "Event.h"
#include "Message.h"

class EventsCatcher {
    int playerId;
public:
    EventsCatcher(int playerId);
    std::queue<Message> getEvents();
    ~EventsCatcher() = default;
};

#endif
