#include <iostream>

#include "../include/DireccionesIP.h"
#include "../include/Socket.h"
#include "../include/ServidorTCP.h"

int main() {
    try {
        char* puerto = "7777";

        Socket peer;
        peer = std::move(
                ServidorTCP::obtenerSocketAceptador(puerto));

        //std::thread t(AtenderClientesEnEspera(peer), recursoRaiz);
        //char entrada = ' ';
        //while (entrada!='q') std::cin >> entrada;

        Socket cliente = peer.aceptar();

        std::string mensaje1;
        cliente.recibir(mensaje1);

        std::string respuesta1 = "hola cliente!";
        cliente.enviar(respuesta1);

        std::string mensaje2;
        cliente.recibir(mensaje2);

        std::string respuesta2 = "todo bien por suerte";
        cliente.enviar(respuesta1);

        std::cout<<mensaje1<<std::endl;
        std::cout<<respuesta1<<std::endl;
        std::cout<<mensaje2<<std::endl;
        std::cout<<respuesta2<<std::endl;

        cliente.cerrar();
        peer.cerrar();
        //t.join();
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
