#ifndef PROTECTEDEVENTQUEUE_H
#define PROTECTEDEVENTQUEUE_H

#include <mutex>
#include <list>
#include "Event.h"

class Message;

/* Cola protegida para encolar los eventos*/
class ProtectedEventsQueue {
    std::list<Message> events;
    std::mutex mutex;
public:
    std::list<Message> popAll();
    bool empty();
    void push(Message& message);
};

#endif
