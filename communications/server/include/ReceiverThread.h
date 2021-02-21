#ifndef RECIVER_THREAD_H
#define RECIVER_THREAD_H

#include "../../common/include/Thread.h"
#include "../../common/include/Socket.h"
//#include "" BlockingQueue
#include "../../common/include/EventSerializer.h"

class ReceiverThread: public Thread{
    bool isDone;
    Socket* skt;
    ProtectedEventQueue& receivedBuffer;

public:
    ReceiverThread(Socket* skt, ProtectedEventQueue& receivedBuffer);
    void run() override;
    bool isDead();
    ~ReceiverThread();

};

#endif