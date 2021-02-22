#ifndef COLADEEVENTOS_SERVER_H
#define COLADEEVENTOS_SERVER_H

#include <atomic>
#include <vector>

class ProtectedEventsQueue;
class BlockingEventsQueue;

class Server {
   // std::vector<Event> updateEvents;
   std::vector<BlockingEventsQueue>& userEvents;
    std::vector<BlockingEventsQueue>& updateEvents;
    std::atomic<bool>& quit;
public:
    Server(    std::vector<BlockingEventsQueue>& userEvents,
               std::vector<BlockingEventsQueue>& updateEvents,
               std::atomic<bool>& quit);

    void operator()();
};

#endif
