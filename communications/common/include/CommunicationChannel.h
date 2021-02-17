#ifndef COMMUNICATIONCHANNEL_H
#define COMMUNICATIONCHANNEL_H

#include <string>
#include <vector>
#include "../include/MatchInfo.h"

typedef std::string str;

class ProtectedLobby;
class Socket;

class CommunicationChannel {
    Socket &socket;
    ProtectedLobby &lobby;

    void addZerosToLeft(str &string, int finalSize);
public:
    CommunicationChannel(Socket& socket, ProtectedLobby& lobby);
    void sendUserNameSubmit(str userName);

    int sendResponseToUserNameSubmit(str &messageReceived);

    void sendRequestOfAvailableMatches();
    void sendResponseToRequestOfMatches();
    void sendRequestOfMatchCreation(int level, int maximumNumberOfPlayers, int userId);
    void sendRequestOfStartMatch(int matchId);

    void sendResponseToRequestOfMatchCreation(str &messageReceived);
    void sendRequestOfMatchCancellation(int matchId);
    void sendResponseToRequestOfMatchCancellation(str &messageReceived);
    void sendRequestOfJoiningAMatch(int matchId, int userId);
    void sendResponseToRequestOfJoiningAMatch(str &messageReceived);
    void sendRequestOfNumberOfUsersInMatch(int matchId);
    void sendResponseToRequestOfNumberOfUsersInMatch(str& messageReceived);
    void sendResponseToRequestOfStartMatch(str& messageReceived);

    static void sendMatchStartedSignal(Socket* socket);

    //post: retorna -1 si el socket del cliente fue cerrado o si el nombre es invalido,
    //      excepcion si el mensaje tiene formato invalido
    //      o el id del nuevo usuario en caso correcto
    int respondUserNameSubmitFromClient();

    void respondMessageFromClient(int userId);
    int receiveClientIdFromServer();

    std::vector<MatchInfo> getMatches(str messageReceived);

    std::vector<MatchInfo> receiveListOfMatches();

    int receiveResponseToRequestOfMatchCreation();
    int receiveResponseOfJoiningAMatch();
    int receiveResponseOfMatchCancellation();
    int receiveResponseOfNumberOfMatches();
    int receiveResponseToRequestOfStartMatch();
};

#endif