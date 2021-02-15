cmake_minimum_required(VERSION 3.17)
project(Client)

set(CMAKE_CXX_STANDARD 11)

add_executable(Client
        src/main.cpp
        src/Exception.cpp
        src/Socket.cpp
        src/IPAddresses.cpp
        src/TCPClient.cpp
        src/CommunicationChannel.cpp src/ProtectedLobby.cpp include/ProtectedLobby.h src/MatchInfo.cpp include/MatchInfo.h src/Match.cpp include/Match.h)