#include "../include/TCPServer.h"
#include "../../common/include/IPAddresses.h"
#include "../../common/include/Socket.h"
#include <netdb.h>

Socket TCPServer::getAcceptorSocket(char* port) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    IPAddresses addresses(nullptr, port, &hints);

    Socket acceptor;
    acceptor.doBind(addresses);
    acceptor.doListen(10);
    return acceptor;
}
