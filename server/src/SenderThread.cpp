#include <common/include/Protocol.h>
#include "../include/SenderThread.h"
#include "common/include/EventSerializer.h"


SenderThread::SenderThread(Socket* skt, BlockingEventsQueue* eventsToSend, int playerId):
        isDone(false), skt(skt), eventsToSend(eventsToSend), playerId(playerId){}

void SenderThread::run(){
    try{
        Protocol protocol(skt);
        while (!isDone){
            Message msg = eventsToSend->pop();
            protocol.send(msg.getMessage());
            isDone = msg.getMessage().substr(0, 3) == std::string("016") &&
                    std::stoi(msg.getMessage().substr(3, 3)) == playerId;
      }
    } catch (std::exception e){}
}

bool SenderThread::isDead(){
    return isDone;
}

SenderThread::~SenderThread(){}