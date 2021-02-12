#include <memory.h>
#include "../include/DireccionesIP.h"
#include "../include/ClienteTCP.h"
#include "../include/Socket.h"
#include <netdb.h>

Socket ClienteTCP::obtenerSocketCliente(char* dominio, char* puerto) {
    struct addrinfo pistas;

    memset(&pistas, 0, sizeof(struct addrinfo));
    pistas.ai_family = AF_INET;
    pistas.ai_socktype = SOCK_STREAM;
    pistas.ai_flags = 0;

    DireccionesIP direcciones(dominio, puerto, &pistas);

    Socket cliente;
    cliente.conectar(direcciones);

    return cliente;
}
