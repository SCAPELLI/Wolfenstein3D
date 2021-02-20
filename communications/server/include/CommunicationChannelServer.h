#ifndef COMMUNICATIONCHANNELSERVER_H
#define COMMUNICATIONCHANNELSERVER_H

#include <string>
#include <vector>
#include "../../common/include/MatchInfo.h"

typedef std::string str;

class ProtectedLobby;
class Socket;

class CommunicationChannelServer {
    Socket &socket;
    ProtectedLobby &lobby;

    void addZerosToLeft(str &string, int finalSize);
public:
    CommunicationChannelServer(Socket& socket, ProtectedLobby& lobby);

    int sendResponseToUserNameSubmit(str &messageReceived);
    void sendResponseToRequestOfMatches();
    void sendResponseToRequestOfMatchCreation(str &messageReceived);
    void sendResponseToRequestOfMatchCancellation(str &messageReceived);
    void sendResponseToRequestOfJoiningAMatch(str &messageReceived);
    void sendResponseToRequestOfNumberOfUsersInMatch(str& messageReceived);
    void sendResponseToRequestOfStartMatch(str& messageReceived);

    static void sendMatchStartedSignal(Socket* socket);

    //post: retorna -1 si el socket del cliente fue cerrado o si el nombre es invalido,
    //      excepcion si el mensaje tiene formato invalido
    //      o el id del nuevo usuario en caso correcto
    int respondUserNameSubmitFromClient();

    void respondMessageFromClient(int userId);
};

#endif
