#ifndef CLIENTETCP_H
#define CLIENTETCP_H

class Socket;

class ClienteTCP {
public:
    static Socket obtenerSocketCliente(char* dominio, char* puerto);
};

#endif
