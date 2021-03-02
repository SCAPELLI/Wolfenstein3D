#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include "../../common/include/Thread.h"
#include "../../common/include/Socket.h"
#include "common/include/ProtectedEventsQueue.h"
/*Thread que se encarga de mandar información*/
class ReceiverThread: public Thread{
    bool isDone;
    Socket* skt;
    ProtectedEventsQueue* receivedBuffer;
    int playerId;

public:
    ReceiverThread(Socket* skt, ProtectedEventsQueue* receivedBuffer, int playerId);
    void run() override;
    bool isDead();
    ~ReceiverThread();

};

#endif