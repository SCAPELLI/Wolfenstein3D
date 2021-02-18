#include <exception>
#include <string>
#include "../include/Exception.h"

Exception::Exception(const std::string& message):
        errorMessage(message) {}
const char* Exception::what() const noexcept {
    return errorMessage.c_str();
}

