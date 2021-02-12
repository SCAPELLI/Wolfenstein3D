#ifndef SERVIDORTCP_H
#define SERVIDORTCP_H

#include <cstring>

class Socket;

class ServidorTCP {
public:
    static Socket obtenerSocketAceptador(char* puerto);
};

#endif
