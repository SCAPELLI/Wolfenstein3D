#include <iostream>
#include <vector>
#include <map>

#include "../include/Excepcion.h"
#include "../include/DireccionesIP.h"
#include "../include/Socket.h"
#include "../include/ClienteTCP.h"

typedef std::string str;

const int USER_NAME_SUBMIT = 0;
const str USER_NAME_SUBMIT_STRING = "000";
const int USER_NAME_SUCCESSFULLY_SUBMITTED = 1;
const str USER_NAME_SUCCESSFULLY_SUBMITTED_STRING = "001";
const int INVALID_USER_NAME = 16;
const str INVALID_USER_NAME_STRING = "016";
const int REQUEST_OF_MATCHES =  2;
const str REQUEST_OF_MATCHES_STRING = "002";
const int LIST_OF_MATCHES = 3;
const str LIST_OF_MATCHES_STRING ="003";
const int REQUEST_OF_MATCH_CREATION = 4;
const str REQUEST_OF_MATCH_CREATION_STRING = "004";
const int MATCH_CREATED_SUCCESSFULLY = 5;
const str MATCH_CREATED_SUCCESSFULLY_STRING = "005";
const int MATCH_NOT_CREATED = 6;
const str MATCH_NOT_CREATED_STRING = "006";
const int REQUEST_OF_START_MATCH = 7;
const str REQUEST_OF_START_MATCH_STRING = "007";
const int MATCH_STARTED_SUCCESSFULLY = 8;
const str MATCH_STARTED_SUCCESSFULLY_STRING = "008";
const int MATCH_NOT_STARTED = 9;
const str MATCH_NOT_STARTED_STRING = "009";
const int REQUEST_OF_MATCH_CANCELLATION = 10;
const str REQUEST_OF_MATCH_CANCELLATION_STRING = "010";
const int MATCH_CANCELLED_SUCCESSFULLY = 11;
const str MATCH_CANCELLED_SUCCESSFULLY_STRING = "011";
const int MATCH_NOT_CANCELLED = 12;
const str MATCH_NOT_CANCELLED_STRING = "012";
const int REQUEST_OF_JOINING_A_MATCH = 13;
const str REQUEST_OF_JOINING_A_MATCH_STRING = "013";
const int SUCCESSFULLY_JOINED_TO_MATCH = 14;
const str SUCCESSFULLY_JOINED_TO_MATCH_STRING = "014";
const int FAILED_TO_JOIN_TO_MATCH = 15;
const str FAILED_TO_JOIN_TO_MATCH_STRING = "015";



class Lobby {
    std::vector<int> matches;
    std::map<str, int> users;
public:
    int addUser(str& userName) {
        int userId = -1;
        if (users[userName] == 0) {
            userId = (int)users.size() + 1;
            users[userName] = userId;
        }
        return userId;
    }
};

class ComunicationProtocol {
    Socket &socket;
    Lobby &lobby;

    void addZerosToLeft(std::string &string, int finalSize) {
        if (string.length() > finalSize)
            throw Excepcion("Invalid message lenght");
        while (string.length() < finalSize)
            string.insert(string.begin(), '0');
    }

public:

    ComunicationProtocol(Socket& socket,Lobby& lobby): socket(socket), lobby(lobby){}

    void sendUserNameSubmit(std::string &userName) {
        socket.enviar(USER_NAME_SUBMIT_STRING + userName);
    }

    void sendResponseToUserNameSubmit(str &messageReceived) {
        str userName = messageReceived.substr(3);
        int userId = lobby.addUser(userName);
        if (userId != -1)
            socket.enviar(USER_NAME_SUCCESSFULLY_SUBMITTED_STRING + std::to_string(userId));
        else
            socket.enviar(INVALID_USER_NAME_STRING);
    }

    void sendRequestOfAvailableMatches() {
        socket.enviar(REQUEST_OF_MATCHES_STRING);
    }

    str sendResponseToRequestOfMatches() {
    }

    void sendRequestOfMatchCreation(int level, int maximumPlayers) {
        str levelString = std::to_string(level);
        addZerosToLeft(levelString, 3);

        str maximumPlayersString = std::to_string(level);
        addZerosToLeft(maximumPlayersString, 3);

        socket.enviar(REQUEST_OF_MATCH_CREATION_STRING + levelString + maximumPlayersString);
    }

    str sendResponseToRequestOfMatchCreation(str &messageReceived) {
    }

    void sendRequestOfMatchCancellation(int matchId) {
        socket.enviar(REQUEST_OF_MATCH_CANCELLATION_STRING + std::to_string(matchId));
    }

    str sendResponseToRequestOfMatchCancellation(str &messageReceived) {
    }

    void sendRequestOfJoiningAMatch(int matchId) {
        socket.enviar(REQUEST_OF_JOINING_A_MATCH_STRING + std::to_string(matchId));
    }

    str sendResponseToRequestOfJoiningAMatch(str &messageReceived) {
    }

    void respondMessageFromClient() {
        str messageReceived;
        socket.recibir(messageReceived);
        int messageCode = std::stoi(messageReceived.substr(0, 3));

        switch (messageCode) {
            case USER_NAME_SUBMIT:
                sendResponseToUserNameSubmit(messageReceived);
                break;
            case REQUEST_OF_MATCHES:
                sendResponseToRequestOfMatches();
                break;
            case REQUEST_OF_MATCH_CREATION:
                sendResponseToRequestOfMatchCreation(messageReceived);
                break;
            case REQUEST_OF_MATCH_CANCELLATION:
                sendResponseToRequestOfMatchCancellation(messageReceived);
                break;
            case REQUEST_OF_JOINING_A_MATCH:
                sendResponseToRequestOfJoiningAMatch(messageReceived);
                break;
            default:
                throw Excepcion("Invalid message from client");
                break;
        }
    }
    void reciveMessageFromServer() {

    }
};

int main() {
    try {
        char* dominio = "localhost";
        char* puerto = "7777";

        Socket cliente;
        cliente = std::move(ClienteTCP::obtenerSocketCliente(dominio, puerto));

        std::string userName = "Urches";




        cliente.cerrar();
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
