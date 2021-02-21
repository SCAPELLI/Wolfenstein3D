#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include "../../common/include/Thread.h"
#include "../../common/include/Socket.h"
//#include "" BlockingQueue

class SenderThread: public Thread{
    bool isDone;
    Socket* skt;
    BlockingEventsQueue& eventsToSend;

    public:
        SenderThread(Socket* skt, BlockingEventsQueue& eventsToSend);
        void run() override;
        bool isDead();
        ~SenderThread();

};

#endif