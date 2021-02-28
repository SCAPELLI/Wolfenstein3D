#include <common/include/Message.h>
#include <common/include/Protocol.h>
#include "../include/ReceiverThread.h"
#include "../../common/EventSerializer.h"
#include "../../common/include/Message.h"



ReceiverThread::ReceiverThread(Socket* skt, ProtectedEventsQueue* receivedBuffer, int playerId):
        isDone(false), skt(skt), receivedBuffer(receivedBuffer), playerId(playerId){}

void ReceiverThread::run() {
    Protocol protocol(skt);
    while(!isDone){
        std::string response;
        //skt->reciveAll(response);
        protocol.receive(response);
        Message msg(response);
        isDone = msg.getMessage().substr(0, 3) == std::string("016") &&
                 std::stoi(msg.getMessage().substr(3, 3)) == playerId;

        receivedBuffer->push(msg);
    }
}

bool ReceiverThread::isDead(){
    return isDone;
}

ReceiverThread::~ReceiverThread(){}