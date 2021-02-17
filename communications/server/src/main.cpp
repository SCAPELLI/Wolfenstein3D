#include <thread>
#include <list>
#include "../../common/include/Socket.h"
#include "../include/TCPServer.h"
#include "../../common/include/ProtectedLobby.h"
#include "../../common/include/CommunicationChannel.h"
#include "../../common/include/AcceptNewUsers.h"

int main() {
    try {
        char* puerto = "7777";

        Socket peer;
        peer = std::move(
                TCPServer::getAcceptorSocket(puerto));

        std::thread t{AcceptNewUsers(peer)};

        char entrada = ' ';
        while (entrada!='q') std::cin >> entrada;

        peer.doClose();
        t.join();
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
