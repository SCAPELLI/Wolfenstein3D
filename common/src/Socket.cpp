#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string>
#include <netdb.h>
#include "../include/Socket.h"
#include "../include/Exception.h"
#include "../include/IPAddresses.h"

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

void Socket::disableSend() const {
    shutdown(fd, SHUT_WR);
}

Socket::~Socket() {
    if (fd != -1) {
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
}

void Socket::doConnect(const IPAddresses& addresses) {
    struct addrinfo* address = addresses.firstAddress();
    bool successfulConnection = false;
    int connectCode;

    while (address != nullptr && !successfulConnection) {
        fd = socket(address->ai_family, address->ai_socktype, 0);
        if (fd != -1) {
            connectCode=connect(fd, address->ai_addr, address->ai_addrlen);
            if (connectCode == -1) {
                address = address->ai_next;
            } else {
                successfulConnection = true;
            }
        } else {
            address = address->ai_next;
        }
    }
}

void Socket::sendAll(const char *message, int numberOfBytesBuffer) const {
    int numberOfBytesSent = 0;
    bool sendFinished = false;

    while (!sendFinished) {
        int sendCode;
        sendCode = send(fd, &message[numberOfBytesSent],
                          numberOfBytesBuffer -
                          numberOfBytesSent,
                        MSG_NOSIGNAL);
        switch (sendCode) {
            case -1:
                throw Exception("Failed to send: " + std::string(strerror(errno)));
                sendFinished = true;
                break;
            case 0:
                sendFinished = true;
                break;
            default:
                numberOfBytesSent =
                        numberOfBytesSent + sendCode;
                sendFinished = numberOfBytesBuffer <= numberOfBytesSent;
                break;
        }
    }
}

int Socket::reciveAll(char *message,
                      int numberOfBytesBuffer) {
    int numberOfBytesReceived = 0;
    bool receiveFinished = (numberOfBytesBuffer <= numberOfBytesReceived);

    while (!receiveFinished) {
        int reciveCode;
        reciveCode = recv(fd, &message[numberOfBytesReceived],
                                     numberOfBytesBuffer -
                                     numberOfBytesReceived,
                          0);
        switch (reciveCode) {
            case -1:
                throw Exception("Failed to recive: " + std::string(strerror(errno)));
                receiveFinished = true;
                break;
            case 0:
                receiveFinished = true;
                doClose();
                break;
            default:
                numberOfBytesReceived =
                        numberOfBytesReceived + reciveCode;
                receiveFinished =
                        numberOfBytesBuffer <= numberOfBytesReceived;
                break;
        }
    }
    return numberOfBytesReceived;
}

void Socket::doBind(const IPAddresses& addresses) {
    struct addrinfo* address = addresses.firstAddress();
    int bindCode;
    int val = 1;

    fd = socket(address->ai_family,
                address->ai_socktype,
                address->ai_protocol);
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    bindCode = bind(fd, address->ai_addr, address->ai_addrlen);
    if (bindCode == -1) {
        throw Exception("Failed to bind: " + std::string(strerror(errno)));
    }
}

void Socket::doListen(int maximumNumberOfWaitingConnections) const {
    int listenCode;
    listenCode = listen(fd, maximumNumberOfWaitingConnections);
    if (listenCode == -1) {
        throw Exception("Failed to listen: " + std::string(strerror(errno)));
    }
}

Socket Socket::doAccept() const {
    Socket peer;
    peer.fd = accept(fd, nullptr, nullptr);
    return peer;
}

void Socket::doClose() {
    if (fd != -1) {
        shutdown(fd, SHUT_RDWR);
        close(fd);
        fd = -1;
    }
}

bool Socket::isAvailable() const {
    return fd != -1;
}

void Socket::sendAll(std::string message) const {

    std::string messageSizeString = std::to_string(message.size());
    while (messageSizeString.length() != 3) {
        messageSizeString.insert(messageSizeString.begin(),'0');
    }
    sendAll(messageSizeString.c_str(), 3);
    sendAll(message.c_str(), message.size());
}

void Socket::reciveAll(std::string& mensaje) {
    char messageLenghtString[3] = "";
    char messageReceived[100] = "";
    int messageLenghtStringSize = reciveAll(&messageLenghtString[0], 3); //Tres es la cantidad de digitos para el largo del mensaje
    if (!isAvailable()) return;

    if (messageLenghtStringSize != 3) throw Exception(
            "Fatal error, the leght of a message is at least" + std::to_string(3) + " bytes");
    int messageSize = std::stoi(std::string(messageLenghtString, messageLenghtStringSize));
    int messageSizeReceived = reciveAll(&messageReceived[0], messageSize);
    if (messageSizeReceived != messageSize) throw Exception(
            "Fatal error, the size of the message received is incorrect\n "
            "size expected: " + std::to_string(messageSize) + " size received: " + std::to_string(messageSize));
    mensaje = std::string(messageReceived, messageSize);
}
