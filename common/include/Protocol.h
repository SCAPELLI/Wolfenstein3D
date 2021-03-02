#ifndef PRUEBAS_PROTOCOL_H
#define PRUEBAS_PROTOCOL_H

#include <string>

class Socket;

class Protocol {
    Socket* socket;
public:
    explicit Protocol(Socket* socket);

    void send(const std::string& message);

    void receive(std::string& message);
};
#endif
