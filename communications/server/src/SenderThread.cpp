#include "SenderThread.h"
#include "../../common/include/EventSerializer.h"


SenderThread::SenderThread(Socket* skt, BlockingEventsQueue& eventsToSend):
        isDone(false), skt(skt), eventsToSend(eventsToSend){}

void SenderThread::run() override{
    try{
        while (!isDone){
            Event event = std::move(eventToSend.pop());
            if (event.thisIsTheQuitEvent()) isDone = true;

            std::string serialization = EventSerializer::serialize(event);
            skt->send(serialization);
        }
    } catch
}

bool SenderThread::isDead(){
    return isDone;
}

SenderThread::~SenderThread(){}