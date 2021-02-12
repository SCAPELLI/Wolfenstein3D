#include "../include/ServidorTCP.h"
#include "../include/DireccionesIP.h"
#include "../include/Socket.h"
#include <netdb.h>

Socket ServidorTCP::obtenerSocketAceptador(char* puerto) {
    struct addrinfo pistas;
    memset(&pistas, 0, sizeof(struct addrinfo));
    pistas.ai_family = AF_INET;
    pistas.ai_socktype = SOCK_STREAM;
    pistas.ai_flags = AI_PASSIVE;
    DireccionesIP direcciones(nullptr, puerto, &pistas);

    Socket aceptador;
    aceptador.enlazar(direcciones);
    aceptador.escuchar(10);
    return aceptador;
}
