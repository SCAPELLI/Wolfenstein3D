cmake_minimum_required(VERSION 3.17)
project(Server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Server
        src/main.cpp
        ../src/TCPServer.cpp
        ../common/src/IPAddresses.cpp
        ../common/src/Exception.cpp
        ../common/src/Socket.cpp
        ../server/src/Match.cpp
        ../common/src/MatchInfo.cpp
        ../server/src/ProtectedLobby.cpp
        ../common/src/Thread.cpp
        ../server/src/CommunicationChannelServer.cpp
        ../server/src/AcceptNewUsersThread.cpp
        ../server/src/UserThread.cpp)