#include "../include/ReceiverThread.h"
#include "../../common/EventSerializer.h"



ReceiverThread::ReceiverThread(Socket* skt, ProtectedEventsQueue& receivedBuffer):
        isDone(false), skt(skt), receivedBuffer(receivedBuffer){}

void ReceiverThread::run() {
    while(!isDone){
        std::string response;
        skt->reciveAll(response);
        Event event = std::move(EventSerializer::deserialize(response));
        isDone = event.thisIsTheQuitEvent();
        receivedBuffer.push(event);
    }
}

bool ReceiverThread::isDead(){
    return isDone;
}

ReceiverThread::~ReceiverThread(){}