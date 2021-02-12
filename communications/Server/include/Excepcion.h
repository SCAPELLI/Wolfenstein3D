#ifndef EXCEPCION_H
#define EXCEPCION_H

#include <string>

class Excepcion: public std::exception {
    std::string mensajeDeError;

public:
    explicit Excepcion(const std::string& mensaje);
    const char* what() const noexcept override;
};

#endif
