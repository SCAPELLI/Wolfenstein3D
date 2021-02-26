#include "../include/ReceiverThread.h"
#include "../../common/EventSerializer.h"
#include "../../common/include/Message.h"



ReceiverThread::ReceiverThread(Socket* skt, ProtectedEventsQueue* receivedBuffer):
        isDone(false), skt(skt), receivedBuffer(receivedBuffer){}

void ReceiverThread::run() {
    while(!isDone){
        std::string response;
        skt->reciveAll(response);
        Message msg(response);
        //Event event = std::move(EventSerializer::deserialize(response));
        //isDone = event.thisIsTheQuitEvent();

        receivedBuffer->push(msg);
    }
}

bool ReceiverThread::isDead(){
    return isDone;
}

ReceiverThread::~ReceiverThread(){}