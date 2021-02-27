#include "../include/SenderThread.h"
#include "../../common/EventSerializer.h"


SenderThread::SenderThread(Socket* skt, BlockingEventsQueue* eventsToSend):
        isDone(false), skt(skt), eventsToSend(eventsToSend){}

void SenderThread::run(){
    try{
        while (!isDone){
            Message msg = std::move(eventsToSend->pop());
            isDone = msg.getMessage().substr(0, 3) == std::string("016");
            skt->sendAll(msg.getMessage());
      }
    } catch (std::exception e){}
}

bool SenderThread::isDead(){
    return isDone;
}

SenderThread::~SenderThread(){}