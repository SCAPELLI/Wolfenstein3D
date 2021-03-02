#ifndef SERVIDORTCP_H
#define SERVIDORTCP_H

#include <cstring>
/* Protocolo del servidor*/
class Socket;

class TCPServer {
public:
    static Socket getAcceptorSocket(const char* host, const char* port);
};

#endif
