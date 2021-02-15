#include <memory.h>
#include "../include/IPAddresses.h"
#include "../include/TCPClient.h"
#include "../include/Socket.h"
#include <netdb.h>

Socket TCPClient::getClientSocket(char* domain, char* port) {
    struct addrinfo pistas;

    memset(&pistas, 0, sizeof(struct addrinfo));
    pistas.ai_family = AF_INET;
    pistas.ai_socktype = SOCK_STREAM;
    pistas.ai_flags = 0;

    IPAddresses direcciones(domain, port, &pistas);

    Socket cliente;
    cliente.doConnect(direcciones);

    return cliente;
}
