#include <common/include/Message.h>
#include <common/include/Protocol.h>
#include "../include/ReceiverThread.h"
#include "common/include/EventSerializer.h"
#include "../../common/include/Message.h"



ReceiverThread::ReceiverThread(Socket* skt, ProtectedEventsQueue* receivedBuffer, int playerId):
        isDone(false), skt(skt), receivedBuffer(receivedBuffer), playerId(playerId){}

void ReceiverThread::run() {
    Protocol protocol(skt);
    while(!isDone){
        std::string response;
        protocol.receive(response);
        if (!skt->isAvailable()) break;
        Message msg(response);
        isDone = msg.getMessage().substr(0, 3) == std::string("016") &&
                 std::stoi(msg.getMessage().substr(3, 3)) == playerId;
        receivedBuffer->push(msg);
    }
    isDone = true;
}

bool ReceiverThread::isDead(){
    return isDone;
}

ReceiverThread::~ReceiverThread(){}