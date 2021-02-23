#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include "../../common/include/Thread.h"
#include "../../common/include/Socket.h"
#include "../../common/ProtectedEventsQueue.h"

class ReceiverThread: public Thread{
    bool isDone;
    Socket* skt;
    ProtectedEventsQueue& receivedBuffer;

public:
    ReceiverThread(Socket* skt, ProtectedEventsQueue& receivedBuffer);
    void run() override;
    bool isDead();
    ~ReceiverThread();

};

#endif