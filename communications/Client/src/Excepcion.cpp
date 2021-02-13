#include <exception>
#include <string>
#include "../include/Excepcion.h"

Excepcion::Excepcion(const std::string& mensaje):
	mensajeDeError(mensaje) {}
const char* Excepcion::what() const noexcept {
    return mensajeDeError.c_str();
}

