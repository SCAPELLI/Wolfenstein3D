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
        ../common/src/Match.cpp
        ../common/src/MatchInfo.cpp
        ../common/src/ProtectedLobby.cpp
        ../common/src/CommunicationChannel.cpp
        ../common/src/Thread.cpp
        ../common/src/AcceptNewUsersThread.cpp
        ../common/src/UserThread.cpp
        ../common/include/IPAddresses.h
        ../common/include/Exception.h
        ../common/include/Socket.h
        ../common/include/Match.h
        ../common/include/MatchInfo.h
        ../common/include/ProtectedLobby.h
        ../common/include/CommunicationChannel.h
        ../common/include/Thread.h
        ../common/include/AcceptNewUsers.h
        ../common/include/UserThread.h)