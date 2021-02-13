cmake_minimum_required(VERSION 3.17)
project(Client)

set(CMAKE_CXX_STANDARD 11)

add_executable(Client
        src/main.cpp
        src/Excepcion.cpp
        src/Socket.cpp
        src/DireccionesIP.cpp
        src/ClienteTCP.cpp)