#ifndef ACCEPTNEWUSERS_H
#define ACCEPTNEWUSERS_H

#include <list>
#include "../include/Socket.h"
#include "../include/ProtectedLobby.h"
#include "../include/UserThread.h"

class AcceptNewUsers {
    Socket& acceptor;
    ProtectedLobby Lobby;
    std::list<Socket> usersSockets;
    std::list<UserThread> usersThreads;

    static bool deadThread(UserThread& thread);
    static bool socketIsNotAvailable(Socket& socket);

public:
    explicit AcceptNewUsers(Socket& acceptor);
    void operator()();
};
#endif
