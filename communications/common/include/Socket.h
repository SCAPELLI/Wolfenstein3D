#ifndef SOCKET_H
#define SOCKET_H

#include <atomic>
#include <iostream>
#include <string>

class IPAddresses;

class Socket {
    int fd;

public:
    Socket();

    ~Socket();

    Socket(Socket &&original) noexcept;
    Socket &operator=(Socket &&original) noexcept;

    Socket (const Socket& anotherSocket) = delete;
    Socket& operator=(const Socket& anotherSocket) = delete;

    void disableSend() const;

    void sendAll(std::string message) const;
    void sendAll(const char *message, int numberOfBytesBuffer) const;

    void reciveAll(std::string& mensaje);
    int reciveAll(char *message,
                  int numberOfBytesBuffer);

    void doBind(const IPAddresses &addresses);
    void doListen(int maximumNumberOfWaitingConnections) const;
    void doConnect(const IPAddresses& addresses);
    void doClose();
    bool isAvailable() const;

    Socket doAccept() const;
};

#endif

