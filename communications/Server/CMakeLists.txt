cmake_minimum_required(VERSION 3.17)
project(Server)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server
        src/main.cpp
        src/IPAddresses.cpp
        src/Exception.cpp
        src/TCPServer.cpp
        src/Socket.cpp
        src/Match.cpp
        src/MatchInfo.cpp
        src/ProtectedLobby.cpp
        src/CommunicationChannel.cpp)