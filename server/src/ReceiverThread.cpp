#include <common/include/Message.h>
#include "../include/ReceiverThread.h"
#include "../../common/EventSerializer.h"



ReceiverThread::ReceiverThread(Socket* skt, ProtectedEventsQueue& receivedBuffer):
        isDone(false), skt(skt), receivedBuffer(receivedBuffer){}

void ReceiverThread::run() {
    while(!isDone){
        std::string response;
        skt->reciveAll(response);
        Event event = std::move(EventSerializer::deserialize(response)); //borrar esto?
        isDone = event.thisIsTheQuitEvent();
        Message received = Message(response);
        receivedBuffer.push(received);
    }
}

bool ReceiverThread::isDead(){
    return isDone;
}

ReceiverThread::~ReceiverThread(){}