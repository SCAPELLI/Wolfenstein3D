#include <common/include/Protocol.h>
#include "../include/SenderThread.h"
#include "../../common/EventSerializer.h"


SenderThread::SenderThread(Socket* skt, BlockingEventsQueue* eventsToSend, int playerId):
        isDone(false), skt(skt), eventsToSend(eventsToSend), playerId(playerId){}

void SenderThread::run(){
    try{
        Protocol protocol(skt);
        while (!isDone){
            Message msg = std::move(eventsToSend->pop());
            isDone = msg.getMessage().substr(0, 3) == std::string("016") &&
                    std::stoi(msg.getMessage().substr(3, 3)) == playerId;
                    //msg.getMessage().substr(0, 3) == std::string("005")) &&;
            protocol.send(msg.getMessage());
      }
    } catch (std::exception e){}
}

bool SenderThread::isDead(){
    return isDone;
}

SenderThread::~SenderThread(){}