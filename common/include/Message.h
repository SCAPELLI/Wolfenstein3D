#ifndef WOLFENSTEIN_MESSAGE_H
#define WOLFENSTEIN_MESSAGE_H
#include <string>

class Message {
    std::string message;
public:
    Message(std::string message);

    Message(const Message& message);
    Message& operator=(const Message& message);
    std::string getMessage();
};

#endif
