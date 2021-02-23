#ifndef EXCEPCION_H
#define EXCEPCION_H

#include <string>
/* Clase de excepcion*/
class Exception: public std::exception {
    std::string errorMessage;

public:
    explicit Exception(std::string  message);
    const char* what() const noexcept override;
};

#endif
