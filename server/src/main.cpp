#include <thread>
#include <list>
#include "../../common/include/Socket.h"
#include "../include/TCPServer.h"
#include "../include/AcceptNewUsers.h"

int main() {
    try {

        const char* port = "7777";
        const char* host = "localhost";

        Socket peer;
        peer = std::move(
                TCPServer::getAcceptorSocket(host, port));

        AcceptNewUsersThread t(peer);
        t.start();

        char entrada = ' ';
        while (entrada!='q') std::cin >> entrada;

        peer.doClose();
        t.join();
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
