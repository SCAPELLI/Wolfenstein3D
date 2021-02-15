#include "../include/Socket.h"
#include "../include/TCPServer.h"
#include "../include/ProtectedLobby.h"
#include "../include/CommunicationChannel.h"

int main() {
    try {
        char* puerto = "7777";

        Socket peer;
        peer = std::move(
                TCPServer::getAcceptorSocket(puerto));

        //std::thread t(AtenderClientesEnEspera(peer), recursoRaiz);
        //char entrada = ' ';
        //while (entrada!='q') std::cin >> entrada;

        Socket client = peer.doAccept();

        ProtectedLobby lobby;
        CommunicationChannel channel(client, lobby);

        int urchesId = channel.respondUserNameSubmitFromClient();
        int carpinchoId = channel.respondUserNameSubmitFromClient();

        while (client.isAvailable())
            channel.respondMessageFromClient(urchesId);

        client.doClose();
        peer.doClose();
        //t.join();
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
