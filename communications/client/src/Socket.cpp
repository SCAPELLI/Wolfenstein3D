#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string>
#include <netdb.h>
#include "../include/Socket.h"
#include "../include/Excepcion.h"
#include "../include/DireccionesIP.h"
#include "../include/Excepcion.h"

Socket::Socket(): fd(-1) {}

Socket::Socket(Socket&& original) noexcept {
    fd = original.fd;
    original.fd=-1;
}

Socket& Socket::operator=(Socket&& original) noexcept {
    fd = original.fd;
    original.fd = -1;
    return *this;
}

void Socket::deshabilitarEnvio() const {
    shutdown(fd, SHUT_WR);
}

Socket::~Socket() {
    if (fd != -1) {
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
}

void Socket::conectar(const DireccionesIP& direcciones) {
    struct addrinfo* address = direcciones.primerDireccion();
    bool conexionExitosa = false;
    int codigoConnect;

    while (address != nullptr && !conexionExitosa) {
        fd = socket(address->ai_family, address->ai_socktype, 0);
        if (fd != -1) {
            codigoConnect=connect(fd, address->ai_addr,address->ai_addrlen);
            if (codigoConnect == -1) {
                address = address->ai_next;
            } else {
                conexionExitosa = true;
            }
        } else {
            address = address->ai_next;
        }
    }
}

void Socket::enviar(const char *mensaje,
                    int cantidadDeBytesBuffer) const {
    int cantidadDeBytesEnviados = 0;
    bool finDeEnvio = false;

    while (!finDeEnvio) {
        int codigoSend;
        codigoSend = send(fd, &mensaje[cantidadDeBytesEnviados],
                          cantidadDeBytesBuffer -
                          cantidadDeBytesEnviados,
                          MSG_NOSIGNAL);
        switch (codigoSend) {
            case -1:
                printf("Error en el envio: %s\n", strerror(errno));
                finDeEnvio = true;
                break;
            case 0:
                finDeEnvio = true;
                break;
            default:
                cantidadDeBytesEnviados =
                        cantidadDeBytesEnviados + codigoSend;
                finDeEnvio = cantidadDeBytesBuffer <= cantidadDeBytesEnviados;
                break;
        }
    }
}

int Socket::recibir(char *mensaje,
                    int cantidadDeBytesBuffer) const {
    bool finDeRecepcion = false;
    int cantidadDeBytesRecibidos = 0;

    while (!finDeRecepcion) {
        int valorRetornadoPorRecv;
        valorRetornadoPorRecv = recv(fd, &mensaje[cantidadDeBytesRecibidos],
                                     cantidadDeBytesBuffer -
                                     cantidadDeBytesRecibidos,
                                     0);
        switch (valorRetornadoPorRecv) {
            case -1:
                throw Excepcion("Error en la recepción: " + std::string(strerror(errno)));
                finDeRecepcion = true;
                break;
            case 0:
                finDeRecepcion = true;
                break;
            default:
                cantidadDeBytesRecibidos =
                        cantidadDeBytesRecibidos + valorRetornadoPorRecv;
                finDeRecepcion =
                        cantidadDeBytesBuffer <= cantidadDeBytesRecibidos;
                break;
        }
    }
    return cantidadDeBytesRecibidos;
}

void Socket::enlazar(const DireccionesIP& direcciones) {
    struct addrinfo* direccion = direcciones.primerDireccion();
    int codigoBind;
    int val = 1;

    fd = socket(direccion->ai_family,
                direccion->ai_socktype,
                direccion->ai_protocol);
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    codigoBind = bind(fd, direccion->ai_addr, direccion->ai_addrlen);
    if (codigoBind == -1) {
        throw Excepcion("Error al intentar enlazar el socket: " 
        				+ std::string(strerror(errno)));
    }
}

void Socket::escuchar(int maximaCantidadDeConexionesEnEspera) const {
    int codigoListen;
    codigoListen = listen(fd, maximaCantidadDeConexionesEnEspera);
    if (codigoListen == -1) {
        throw Excepcion("Error al intentar escuchar desde el socket: " 
        				+ std::string(strerror(errno)));
    }
}

Socket Socket::aceptar() const {
    Socket peer;
    peer.fd = accept(fd, nullptr, nullptr);
    return peer;
}

void Socket::cerrar() {
    shutdown(fd, SHUT_RDWR);
    close(fd);
    fd = -1;
}

bool Socket::estaHabilitado() const {
    return fd != -1;
}

void Socket::enviar(std::string messageToSend) const {

    std::string messageSizeString = std::to_string(messageToSend.size());
    while (messageSizeString.length() != 3) {
        messageSizeString.insert(messageSizeString.begin(),'0');
    }
    enviar(messageSizeString.c_str(), 3);
    enviar(messageToSend.c_str(), messageToSend.size());
}

void Socket::recibir(std::string& messageReceivedString) const {
    char messageLenghtString[3] = "";
    char messageReceived[100] = "";
    int messageLenghtStringSize = recibir(&messageLenghtString[0], 3); //Tres es la cantidad de digitos para el largo del mensaje
    if (messageLenghtStringSize != 3) throw Excepcion(
            "Fatal error, the leght of a message is at least" + std::to_string(3) + " bytes");
    int messageSize = std::stoi(std::string(messageLenghtString, messageLenghtStringSize));
    int messageSizeReceived = recibir(&messageReceived[0], messageSize);
    if (messageSizeReceived != messageSize) throw Excepcion(
            "Fatal error, the size of the message received is incorrect\n "
            "size expected: " + std::to_string(messageSize) + " size received: " + std::to_string(messageSize));
    messageReceivedString = std::string(messageReceived, messageSize);
}
