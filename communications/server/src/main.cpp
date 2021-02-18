#include <thread>
#include <list>
#include "../../common/include/Socket.h"
#include "../include/TCPServer.h"
#include "../../common/include/ProtectedLobby.h"
#include "../../common/include/CommunicationChannel.h"
#include "../../common/include/AcceptNewUsers.h"

int main() {
    try {

        const char* port = "7777";

        Socket peer;
        peer = std::move(
                TCPServer::getAcceptorSocket(port));

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
