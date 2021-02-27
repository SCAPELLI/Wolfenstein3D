#include <netdb.h>
#include <vector>
#include <cstring>
#include "Protocol.h"
#include "Socket.h"

Protocol::Protocol(Socket* socket): socket(socket) {}

void Protocol::send(const std::string& message) {
    auto lenght = (uint32_t)message.length();
    lenght = htons(lenght);

    size_t buffer_lenght = sizeof(uint32_t) + message.length();

    std::vector<uint8_t> buffer(buffer_lenght);
    memcpy(&buffer[0], &lenght, sizeof(uint32_t));
    memcpy(&buffer[sizeof(uint32_t)], &message[0], message.length());

    socket->sendAll((char*)&buffer[0], (int)buffer_lenght);
}

void Protocol::receive(std::string& message) {
    std::vector<uint8_t> buffer_size(sizeof(uint32_t));
    socket->reciveAll((char*)&buffer_size[0], (int)sizeof(uint32_t));

    uint32_t size = *((uint32_t*)(&buffer_size[0]));
    size = ntohs(size);

    std::vector<uint8_t> buffer(size);
    socket->reciveAll((char*)&buffer[0], (int)size);

    message = std::string (buffer.begin(), buffer.end());
}
