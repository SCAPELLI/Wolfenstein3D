#include <string>
#include "../include/Message.h"

Message::Message(std::string message): message(message) {}

Message::Message(const Message& aMessage) {
    message = aMessage.message;
}
Message& Message::operator=(const Message& aMessage) {
    message = aMessage.message;
    return *this;
}
Message::getMessage() {
    return message;
}

