cmake_minimum_required(VERSION 3.17)
project(Client)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Client
        src/main.cpp
        ../common/src/Exception.cpp
        ../common/src/Socket.cpp
        ../common/src/IPAddresses.cpp
        src/TCPClient.cpp
        ../common/src/CommunicationChannel.cpp
        ../common/src/ProtectedLobby.cpp
        ../common/src/MatchInfo.cpp
        ../common/src/Match.cpp
        ../common/src/Thread.cpp
        src/Client.cpp include/Client.h)