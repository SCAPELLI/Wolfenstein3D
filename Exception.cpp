#include <exception>
#include <string>
#include <utility>
#include "Exception.h"

Exception::Exception(std::string message):
	errorMessage(std::move(message)) {}
const char* Exception::what() const noexcept {
    return errorMessage.c_str();
}

