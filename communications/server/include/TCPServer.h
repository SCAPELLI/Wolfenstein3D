#ifndef SERVIDORTCP_H
#define SERVIDORTCP_H

#include <cstring>

class Socket;

class TCPServer {
public:
    static Socket getAcceptorSocket(char* port);
};

#endif
