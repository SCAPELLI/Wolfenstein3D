#include "../include/AcceptNewUsers.h"
#include "../include/UserThread.h"
#include "../include/Thread.h"

bool AcceptNewUsers::deadThread(UserThread& thread) {
    if (thread.runFinished) {
        thread.join();
        return true;
    }
    return false;
}
bool AcceptNewUsers::socketIsNotAvailable(Socket& socket) {
    return !socket.isAvailable();
}

AcceptNewUsers::AcceptNewUsers(Socket& acceptor): acceptor(acceptor) {}

void AcceptNewUsers::operator()() {
    ProtectedLobby lobby;
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
}

