#include "../include/AcceptNewUsers.h"
#include "../../common/include/Socket.h"

bool AcceptNewUsersThread::deadThread(UserThread& thread) {
    if (thread.runFinished) {
        thread.join();
        return true;
    }
    return false;
}
bool AcceptNewUsersThread::socketIsNotAvailable(Socket& socket) {
    return !socket.isAvailable();
}

AcceptNewUsersThread::AcceptNewUsersThread(Socket& acceptor, char* configPath): acceptor(acceptor), configPath(configPath) {}

void AcceptNewUsersThread::run() {
    ProtectedLobby lobby(configPath);
    while (acceptor.isAvailable()) {
        usersSockets.emplace_back(std::move(acceptor.doAccept()));
        if (usersSockets.back().isAvailable()) {
            usersThreads.emplace_back(usersSockets.back(), lobby);
            usersThreads.back().start();
        }
        usersThreads.remove_if(deadThread);
        usersSockets.remove_if(socketIsNotAvailable);
    }
    for (auto& user: usersSockets) if (user.isAvailable()) user.doClose();
    for (auto& userThread: usersThreads) userThread.join();
    lobby.JoinMatches();
}

