#include <netdb.h>
#include <vector>
#include <cstring>
#include "../include/Protocol.h"
#include "../include/Socket.h"

Protocol::Protocol(Socket* socket): socket(socket) {}

void Protocol::send(const std::string& message) {
    auto lenght = (uint32_t)message.length();
    lenght = htons(lenght);

    size_t buffer_lenght = sizeof(uint32_t) + message.length();

    std::vector<uint8_t> buffer(buffer_lenght);
    memcpy(&buffer[0], &lenght, sizeof(uint32_t));
    memcpy(&buffer[sizeof(uint32_t)], &message[0], message.length());

    socket->sendAll(&buffer[0], buffer_lenght);
}

void Protocol::receive(std::string& message) {
    std::vector<uint8_t> buffer_size(sizeof(uint32_t));
    socket->reciveAll(&buffer_size[0], sizeof(uint32_t));

    uint32_t size = *((uint32_t*)(&buffer_size[0]));
    size = ntohs(size);

    std::vector<uint8_t> buffer(size);
    socket->reciveAll(&buffer[0], size);

    message = std::string (buffer.begin(), buffer.end());
}
