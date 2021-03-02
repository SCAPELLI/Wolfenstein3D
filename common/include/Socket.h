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

    void sendAll(const uint8_t* message, size_t numberOfBytesBuffer) const;
    int reciveAll(uint8_t* message, size_t numberOfBytesBuffer);
    void doBind(const IPAddresses &addresses);
    void doListen(int maximumNumberOfWaitingConnections) const;
    void doConnect(const IPAddresses& addresses);
    void doClose();
    bool isAvailable() const;

    Socket doAccept() const;
};

#endif

