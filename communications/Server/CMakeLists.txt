cmake_minimum_required(VERSION 3.17)
project(Server)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server
        src/main.cpp
        src/DireccionesIP.cpp
        src/Excepcion.cpp
        src/ServidorTCP.cpp
        src/Socket.cpp)