#ifndef COLADEEVENTOS_SERVER_H
#define COLADEEVENTOS_SERVER_H

#include <atomic>

class ProtectedEventsQueue;

class Server {
   // std::vector<Event> updateEvents;
    ProtectedEventsQueue& userEvents;
    ProtectedEventsQueue& updateEvents;
    std::atomic<bool>& quit;
public:
    Server(ProtectedEventsQueue& userEvents, ProtectedEventsQueue& updateEvents,
           std::atomic<bool>& quit);

    void operator()();
};

#endif
