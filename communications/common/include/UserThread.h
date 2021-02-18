#ifndef USERTHREAD_H
#define USERTHREAD_H

#include <atomic>
#include "../include/Thread.h"

class Socket;
class ProtectedLobby;

class UserThread: public Thread {
    Socket& user;
    ProtectedLobby& lobby;
public:
    std::atomic<bool> runFinished;

    UserThread(Socket& user, ProtectedLobby& lobby);
    void run() override;
};

#endif
