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

class Match {
    std::map<str, int> users;
    int maximumNumberOfPlayers;
    int matchId;
    int levelId;
public:
    Match(int matchId, int levelId, int maximumNumberOfPlayers):
        matchId(matchId),levelId(levelId), maximumNumberOfPlayers(maximumNumberOfPlayers) {}
    void addUser(str userName, int userId) {
        users[userName] = userId;
    }
    int getMatchId() {
        return matchId;
    }
    int getLevelId() {
        return levelId;
    }
    int getMaximumNumberOfPlayers() {
        return maximumNumberOfPlayers;
    }
    int getActualNumberOfPlayers() {
        return users.size();
    }
    bool sameIdAs(int aMatchId) {
        return matchId == aMatchId;
    }

    bool isNoFull() {
        return maximumNumberOfPlayers > users.size();
    }
};

class Lobby {
    std::vector<Match> matches;
    std::map<str, int> users;
    int reference;
public:
    Lobby(): reference(0) {};
    int addUser(str& userName) {
        int userId = -1;
        if (users[userName] == 0) {
            userId = (int)users.size();
            users[userName] = userId;
        }
        return userId;
    }
    str getUserName(int userId) {
        str userName;
        for (auto& user: users) {
            if (user.second == userId)
                userName = user.first;
        }
        return userName;
    }
    std::vector<Match> getMatches() {
        return matches;
    }
    int createANewMatch(int levelId, int maximumNumberOfPlayers, int userId) {
        // queda pendiente la logica de validacion de nivel existente
        // en esta primer version solo es valido el nivel 1

        if ((maximumNumberOfPlayers < 1) or (levelId != 1))
            return -1;
        else {
            ++reference;
            matches.emplace_back(reference, levelId, maximumNumberOfPlayers);
            matches.back().addUser(getUserName(userId), userId);
            return reference;
        }
    }
    int addUserToMatch(int matchId, int userId) {
        for (Match& match: matches) {
            if (match.sameIdAs(matchId) and match.isNoFull()) {
                match.addUser(getUserName(userId), userId);
                return 0;
            }
        }
        return -1;
    }
};

class MatchInfo {
    int actualNumberOfPlayers;
    int maximumNumberOfPlayers;
    int matchId;
    int levelId;
public:
    MatchInfo(int matchId, int levelId, int maximumNumberOfPlayers, int actualNumberOfPlayers):
        matchId(matchId), levelId(levelId),maximumNumberOfPlayers(maximumNumberOfPlayers),
        actualNumberOfPlayers(actualNumberOfPlayers) {}
};

class ComunicationProtocol {
    Socket &socket;
    Lobby &lobby;

    void addZerosToLeft(std::string &string, int finalSize) {
        if (string.length() > finalSize)
            throw Excepcion("the message '" + string +"' is to long, cannot add zeros to left");
        while (string.length() < finalSize)
            string.insert(string.begin(), '0');
    }

public:
    ComunicationProtocol(Socket& socket,Lobby& lobby): socket(socket), lobby(lobby){}

    void sendUserNameSubmit(std::string userName) {
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

    void sendResponseToRequestOfMatches() {
        // Cantidad de partidas [#] (3 bytes)
        // Match id [M] (3 bytes)
        // Level id [L] (3 bytes)
        // Tope de numero de jugadores [T] (3 bytes)
        // Actual numero de jugadores [A] (3 bytes)
        // Ejemplo:
        // ___2###MMMLLLTTTAAA###MMMLLLTTTAAA
        std::vector<Match> matches = lobby.getMatches();

        str response = LIST_OF_MATCHES_STRING;
        str numberOfMatches = std::to_string(matches.size());
        addZerosToLeft(numberOfMatches, 3);
        response.append(numberOfMatches);

        for (Match& match: matches) {
            str matchId = std::to_string(match.getMatchId());
            str levelId = std::to_string(match.getLevelId());
            str maximumNumberOfPlayers = std::to_string(match.getMaximumNumberOfPlayers());
            str actualNumberOfPlayers = std::to_string(match.getActualNumberOfPlayers());
            addZerosToLeft(matchId, 3);
            addZerosToLeft(levelId, 3);
            addZerosToLeft(maximumNumberOfPlayers, 3);
            addZerosToLeft(actualNumberOfPlayers, 3);
            response.append(matchId.append(levelId).append(maximumNumberOfPlayers).append(actualNumberOfPlayers));
        }
        socket.enviar(response);
    }

    void sendRequestOfMatchCreation(int level, int maximumNumberOfPlayers, int userId) {
        str levelString = std::to_string(level);
        addZerosToLeft(levelString, 3);

        str maximumPlayersString = std::to_string(maximumNumberOfPlayers);
        addZerosToLeft(maximumPlayersString, 3);

        str userIdString = std::to_string(userId);
        addZerosToLeft(userIdString, 3);

        socket.enviar(REQUEST_OF_MATCH_CREATION_STRING + levelString + maximumPlayersString + userIdString);
    }

    void sendResponseToRequestOfMatchCreation(str &messageReceived) {
        int levelId = std::stoi(messageReceived.substr(3, 3));
        int maximumNumberOfPlayers = std::stoi(messageReceived.substr(6, 3));
        int userId = std::stoi(messageReceived.substr(9,3));

        int matchId = lobby.createANewMatch(levelId, maximumNumberOfPlayers, userId);
        if (matchId == -1) {
            socket.enviar(MATCH_NOT_CREATED_STRING);
        } else {
            str matchIdString = std::to_string(matchId);
            addZerosToLeft(matchIdString, 3);
            socket.enviar(MATCH_CREATED_SUCCESSFULLY_STRING + matchIdString);
        }
    }

    void sendRequestOfMatchCancellation(int matchId) {
        socket.enviar(REQUEST_OF_MATCH_CANCELLATION_STRING + std::to_string(matchId));
    }

    void sendResponseToRequestOfMatchCancellation(str &messageReceived) {
    }

    void sendRequestOfJoiningAMatch(int matchId, int userId) {
        str matchIdString = std::to_string(matchId);
        addZerosToLeft(matchIdString, 3);

        str userIdString = std::to_string(userId);
        addZerosToLeft(userIdString, 3);

        socket.enviar(REQUEST_OF_JOINING_A_MATCH_STRING + matchIdString + userIdString);
    }

    void sendResponseToRequestOfJoiningAMatch(str &messageReceived) {
        int matchId = std::stoi(messageReceived.substr(3, 3));
        int userId = std::stoi(messageReceived.substr(6, 3));

        int response = lobby.addUserToMatch(matchId, userId);
        if (response == -1)
            socket.enviar(FAILED_TO_JOIN_TO_MATCH_STRING);
        else
            socket.enviar(SUCCESSFULLY_JOINED_TO_MATCH_STRING);
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
    int reciveClientIdFromServer() {
        str messageReceived;
        socket.recibir(messageReceived);
        int messageCode = std::stoi(messageReceived.substr(0, 3));
        if (messageCode ==  USER_NAME_SUCCESSFULLY_SUBMITTED)
            return std::stoi(messageReceived.substr(3));
        if (messageReceived == INVALID_USER_NAME_STRING)
            return -1;
        throw Excepcion("Message not expected");
    }

    std::vector<MatchInfo> getMatches(str messageReceived) {
        int numberOfMatches = std::stoi(messageReceived.substr(3, 3));
        str matchesInfo = messageReceived.substr(6);

        std::vector<MatchInfo> matches;

        if (matchesInfo.size() != (numberOfMatches * 12))
            throw Excepcion("Invalid list of matches");
        for (int matchNumber = 0; matchNumber < numberOfMatches; ++matchNumber) {
            int matchId = std::stoi(matchesInfo.substr((matchNumber * 12) + 0, 3));
            int levelId = std::stoi(matchesInfo.substr((matchNumber * 12) + 3, 3));
            int maximumNumberOfPlayers = std::stoi(matchesInfo.substr((matchNumber * 12) + 6, 3));
            int actualNumberOfPlayers = std::stoi(matchesInfo.substr((matchNumber * 12) + 9, 3));
            matches.emplace_back(matchId, levelId, maximumNumberOfPlayers, actualNumberOfPlayers);
        }
        return matches;
    }

    std::vector<MatchInfo> reciveListOfMatches() {
        str messageReceived;
        socket.recibir(messageReceived);
        int messageCode = std::stoi(messageReceived.substr(0, 3));
        if (messageCode != LIST_OF_MATCHES)
            throw Excepcion("Message not expected");
        return getMatches(messageReceived);
    }

    int reciveRespondToRequestOfMatchCreation() {
        str messageReceived;
        socket.recibir(messageReceived);
        int messageCode = std::stoi(messageReceived.substr(0, 3));
        if (messageCode == MATCH_CREATED_SUCCESSFULLY)
            return std::stoi(messageReceived.substr(3, 3));
        if (messageCode == MATCH_NOT_CREATED)
            return -1;
        throw Excepcion("Message not expected");
    }

    int reciveRespondOfJoiningAMatch() {
        str messageReceived;
        socket.recibir(messageReceived);
        int messageCode = std::stoi(messageReceived.substr(0, 3));
        if (messageCode == SUCCESSFULLY_JOINED_TO_MATCH)
            return 0;
        if (messageCode == FAILED_TO_JOIN_TO_MATCH)
            return -1;
        throw Excepcion("Message not expected");
    }

};

int main() {
    try {
        char* dominio = "localhost";
        char* puerto = "7777";

        Socket client;
        client = std::move(ClienteTCP::obtenerSocketCliente(dominio, puerto));
        Lobby lobby;
        ComunicationProtocol channel(client, lobby);

        channel.sendUserNameSubmit("Urches");
        int urchesId = channel.reciveClientIdFromServer();

        channel.sendUserNameSubmit("srCarpincho");
        int carpinchoId = channel.reciveClientIdFromServer();

        channel.sendRequestOfMatchCreation(1, 1, urchesId);
        int matchId = channel.reciveRespondToRequestOfMatchCreation();

        channel.sendRequestOfJoiningAMatch(matchId, carpinchoId);
        int response = channel.reciveRespondOfJoiningAMatch();

        channel.sendRequestOfAvailableMatches();
        std::vector<MatchInfo> matches = channel.reciveListOfMatches();

        cliente.cerrar();
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
