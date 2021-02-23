#include "../include/SenderThread.h"
#include "../../common/EventSerializer.h"


SenderThread::SenderThread(Socket* skt, BlockingEventsQueue* eventsToSend):
        isDone(false), skt(skt), eventsToSend(eventsToSend){}

void SenderThread::run(){
    try{
        while (!isDone){
            Event event = std::move(eventsToSend->pop());
            if (event.thisIsTheQuitEvent()) isDone = true;

            std::string serialization = EventSerializer::serialize(event);
            skt->sendAll(serialization);
      }
    } catch (std::exception e){}
}

bool SenderThread::isDead(){
    return isDone;
}

SenderThread::~SenderThread(){}