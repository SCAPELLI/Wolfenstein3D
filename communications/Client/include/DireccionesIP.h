#ifndef DIRECCIONESIP_H
#define DIRECCIONESIP_H

class DireccionesIP {
    struct addrinfo* direcciones;
public:
    DireccionesIP(char* dominio, char* puerto, struct addrinfo* pistas);

    struct addrinfo* primerDireccion() const;

    ~DireccionesIP();
};

#endif
