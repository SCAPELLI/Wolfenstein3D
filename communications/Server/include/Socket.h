#ifndef SOCKET_H
#define SOCKET_H

#include <atomic>
#include <iostream>
#include <string>

class DireccionesIP;

class Socket {
    int fd;

public:
    Socket();

    ~Socket();

    Socket(Socket &&original) noexcept;
    Socket &operator=(Socket &&original) noexcept;

    Socket (const Socket& otroSocket) = delete;
    Socket& operator=(const Socket& otroSocket) = delete;

    void deshabilitarEnvio() const;

    void enviar(std::string& mensaje) const;
    void enviar(const char *mensaje, int cantidadDeBytesBuffer) const;

    void recibir(std::string& mensaje) const;
    int recibir(char *mensaje,
                int cantidadDeBytesBuffer) const;

    void enlazar(const DireccionesIP &direcciones);
    void escuchar(int maximaCantidadDeConexionesEnEspera) const;
    void conectar(const DireccionesIP& direcciones);
    void cerrar();
    bool estaHabilitado() const;

    Socket aceptar() const;
};

#endif

