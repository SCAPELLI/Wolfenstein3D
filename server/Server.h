#ifndef COLADEEVENTOS_SERVER_H
#define COLADEEVENTOS_SERVER_H

#include <atomic>
#include <vector>

class ProtectedEventsQueue;
class BlockingEventsQueue;

class Server {
   ProtectedEventsQueue& userEvents;
    std::vector<BlockingEventsQueue>& updateEvents;
    std::atomic<bool>& quit;
public:
    Server(    ProtectedEventsQueue& userEvents,
               std::vector<BlockingEventsQueue>& updateEvents,
               std::atomic<bool>& quit);

    void operator()();
};

#endif
