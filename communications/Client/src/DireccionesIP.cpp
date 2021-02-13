#include "../include/DireccionesIP.h"
#include <netdb.h>
#include <string>
#include "../include/Excepcion.h"

DireccionesIP::DireccionesIP(char* dominio,
                             char* puerto,
                             struct addrinfo* pistas) {
    int codigoGetAddrInfo;
    direcciones = nullptr;

    codigoGetAddrInfo = getaddrinfo(dominio, puerto, pistas, &direcciones);
    //CAMBIAR POR EXCEPCION
    if (codigoGetAddrInfo != 0) {
    	throw Excepcion("Dominio o puerto invalido: " 
        				+ std::string(gai_strerror(codigoGetAddrInfo)));
    }
}

struct addrinfo* DireccionesIP::primerDireccion() const {
    return direcciones;
}

DireccionesIP::~DireccionesIP() {
    freeaddrinfo(direcciones);
}
