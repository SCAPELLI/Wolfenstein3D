#ifndef CLIENTETCP_H
#define CLIENTETCP_H

class Socket;

class TCPClient {
public:
    static Socket getClientSocket(char* domain, char* port);
};

#endif
