cmake_minimum_required(VERSION 3.17)
project(Server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Server
        src/main.cpp
        ../common/src/IPAddresses.cpp
        ../common/src/Exception.cpp
        ../src/TCPServer.cpp
        ../common/src/Socket.cpp
        ../common/src/Match.cpp
        ../common/src/MatchInfo.cpp
        ../common/src/ProtectedLobby.cpp
        ../common/src/CommunicationChannel.cpp
        ../common/src/Thread.cpp
        ../common/src/AcceptNewUsers.cpp
        ../common/src/UserThread.cpp)