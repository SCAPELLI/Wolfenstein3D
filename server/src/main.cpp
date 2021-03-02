#include <thread>
#include <list>
#include "../../common/include/Socket.h"
#include "../include/TCPServer.h"
#include "../include/AcceptNewUsers.h"
#include "../common/include/Exception.h"
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>

int main(int argc, char* argv[]) {
    try {

    	if (argc != 2) throw Exception("Bad arguments input"); 
    	YAML::Node input = YAML::LoadFile(argv[1]);

    	std::string port = input["port"].as<std::string>();
    	std::string host = input["host"].as<std::string>();

        Socket peer;
        peer = std::move(
                TCPServer::getAcceptorSocket(host.c_str(), port.c_str()));

        AcceptNewUsersThread t(peer, argv[1]);
        t.start();

        std::cout<<"Welcome to Wolfenstein 3D Server"<<std::endl;
        std::cout<<"New players can log in using port <"<<port<<"> and server <"<<host<<">"<<std::endl<<std::endl;;
        std::cout<<"For further instructions please refer to https://github.com/SCAPELLI/Wolfenstein3D"<<std::endl<<std::endl;

        std::cout<<"To close the server enter 'q'"<<std::endl;

        char entrada = ' ';
        while (entrada!='q') std::cin >> entrada;

        peer.doClose();
        t.join();
        std::cout<<"Wolfenstein 3D Server closed successfully"<<std::endl;
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
