#ifndef ACCEPTNEWUSERSTHREAD_H
#define ACCEPTNEWUSERSTHREAD_H

#include <list>
#include "../include/ProtectedLobby.h"
#include "../include/UserThread.h"

class AcceptNewUsersThread: public Thread{
    Socket& acceptor;
    ProtectedLobby Lobby;
    std::list<Socket> usersSockets;
    std::list<UserThread> usersThreads;

    static bool deadThread(UserThread& thread);
    static bool socketIsNotAvailable(Socket& socket);

public:
    explicit AcceptNewUsersThread(Socket& acceptor);
    void run() override;
};
#endif
