#ifndef CLIENTETCP_H
#define CLIENTETCP_H

class Socket;

class TCPClient {
public:
    static Socket getClientSocket(const char* domain, const char* port);
};

#endif
