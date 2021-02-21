#include "../include/CommunicationChannelServer.h"
#include "../../common/include/Exception.h"
#include "../include/Match.h"
#include "../include/ProtectedLobby.h"
#include "../../common/include/Socket.h"

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
const int MATCH_FINISHED_SUCCESSFULLY = 8;
const str MATCH_FINISHED_SUCCESSFULLY_STRING = "008";
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
const int MATCH_STARTED_SIGNAL = 14;
const str MATCH_STARTED_SIGNAL_STRING = "014";
const int FAILED_TO_JOIN_TO_MATCH = 15;
const str FAILED_TO_JOIN_TO_MATCH_STRING = "015";
const int REQUEST_OF_NUMBER_OF_USERS_IN_MATCH = 16;
const str REQUEST_OF_NUMBER_OF_USERS_IN_MATCH_STRING = "016";
const int SUCCESSFULLY_GOT_THE_NUMBER_OF_USERS_IN_MATCH = 17;
const str SUCCESSFULLY_GOT_THE_NUMBER_OF_USERS_IN_MATCH_STRING = "017";
const int FAILED_TO_GET_THE_NUMBER_OF_USERS_IN_MATCH = 18;
const str FAILED_TO_GET_THE_NUMBER_OF_USERS_IN_MATCH_STRING = "018";

void CommunicationChannelServer::addZerosToLeft(std::string &string, int finalSize) {
    if (string.length() > finalSize)
        throw Exception("the message '" + string + "' is to long, cannot add zeros to left");
    while (string.length() < finalSize)
        string.insert(string.begin(), '0');
}

CommunicationChannelServer::CommunicationChannelServer(Socket& socket, ProtectedLobby& lobby): socket(socket), lobby(lobby){}

int CommunicationChannelServer::sendResponseToUserNameSubmit(str &messageReceived) {
    str userName = messageReceived.substr(3);
    int userId = lobby.addUser(userName);
    if (userId != -1)
        socket.sendAll(USER_NAME_SUCCESSFULLY_SUBMITTED_STRING + std::to_string(userId));
    else
        socket.sendAll(INVALID_USER_NAME_STRING);
    return userId;
}

void CommunicationChannelServer::sendResponseToRequestOfMatches() {
    // Cantidad de partidas [#] (3 bytes)
    // Match id [M] (3 bytes)
    // Level id [L] (3 bytes)
    // Tope de numero de jugadores [T] (3 bytes)
    // Actual numero de jugadores [A] (3 bytes)
    // Ejemplo:
    // ___2###MMMLLLTTTAAA###MMMLLLTTTAAA
    std::vector<MatchInfo> matches = lobby.getMatchesInfo();

    str response = LIST_OF_MATCHES_STRING;
    str numberOfMatches = std::to_string(matches.size());
    addZerosToLeft(numberOfMatches, 3);
    response.append(numberOfMatches);

    for (MatchInfo& match: matches) {
        str matchId = std::to_string(match.getMatchId());
        str levelId = std::to_string(match.getLevelId());
        str maximumNumberOfPlayers = std::to_string(match.getMaximumNumberOfUsers());
        str actualNumberOfPlayers = std::to_string(match.getActualNumberOfUsers());
        addZerosToLeft(matchId, 3);
        addZerosToLeft(levelId, 3);
        addZerosToLeft(maximumNumberOfPlayers, 3);
        addZerosToLeft(actualNumberOfPlayers, 3);
        response.append(matchId.append(levelId).append(maximumNumberOfPlayers).append(actualNumberOfPlayers));
    }
    socket.sendAll(response);
}

void CommunicationChannelServer::sendResponseToRequestOfMatchCreation(str &messageReceived) {
    int levelId = std::stoi(messageReceived.substr(3, 3));
    int userId = std::stoi(messageReceived.substr(6,3));
    int maximumNumberOfPlayers = std::stoi(messageReceived.substr(9));

    if (maximumNumberOfPlayers > 999) {
        socket.sendAll(MATCH_NOT_CREATED_STRING);
        return;
    }
    int matchId = lobby.createANewMatch(levelId, maximumNumberOfPlayers, userId, &socket);
    if (matchId == -1) {
        socket.sendAll(MATCH_NOT_CREATED_STRING);
    } else {
        str matchIdString = std::to_string(matchId);
        addZerosToLeft(matchIdString, 3);
        socket.sendAll(MATCH_CREATED_SUCCESSFULLY_STRING + matchIdString);
    }
}

void CommunicationChannelServer::sendResponseToRequestOfMatchCancellation(str &messageReceived) {
    int matchId = std::stoi(messageReceived.substr(3));
    int response = lobby.cancelMatch(matchId);

    if (response == -1)
        socket.sendAll(MATCH_NOT_CANCELLED_STRING);
    else
        socket.sendAll(MATCH_CANCELLED_SUCCESSFULLY_STRING);
}

void CommunicationChannelServer::sendResponseToRequestOfJoiningAMatch(str &messageReceived) {
    int matchId = std::stoi(messageReceived.substr(3, 3));
    int userId = std::stoi(messageReceived.substr(6, 3));

    int response = lobby.addUserToMatch(matchId, userId, &socket);
    if (response == -1)
        socket.sendAll(FAILED_TO_JOIN_TO_MATCH_STRING);
}

void CommunicationChannelServer::sendResponseToRequestOfNumberOfUsersInMatch(str& messageReceived) {
    int matchId = std::stoi(messageReceived.substr(3));
    int response = lobby.numberOfUsersInMatch(matchId);
    if (response == -1)
        socket.sendAll(FAILED_TO_GET_THE_NUMBER_OF_USERS_IN_MATCH_STRING);
    else
        socket.sendAll(SUCCESSFULLY_GOT_THE_NUMBER_OF_USERS_IN_MATCH_STRING + std::to_string(response));
}

void CommunicationChannelServer::sendResponseToRequestOfStartMatch(str& messageReceived) {
    int matchId = std::stoi(messageReceived.substr(3));

    int response = lobby.startMatch(matchId);

    if (response == -1)
        socket.sendAll(MATCH_NOT_STARTED_STRING);
}

void CommunicationChannelServer::sendMatchStartedSignal(Socket* socket) {
    socket->sendAll(MATCH_STARTED_SIGNAL_STRING);
}

int CommunicationChannelServer::respondUserNameSubmitFromClient() {
    str messageReceived;
    socket.reciveAll(messageReceived);
    if (!socket.isAvailable()) return -1;

    int messageCode = std::stoi(messageReceived.substr(0, 3));

    if (messageCode != USER_NAME_SUBMIT)
        throw Exception("User Submit Expected");
    return sendResponseToUserNameSubmit(messageReceived);
}

void CommunicationChannelServer::respondMessageFromClient(int userId) {
    str messageReceived;
    socket.reciveAll(messageReceived);
    if (!socket.isAvailable() or messageReceived.empty()) {
        lobby.removeUser(userId);
        return;
    };
    int messageCode = std::stoi(messageReceived.substr(0, 3));

    switch (messageCode) {
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
        case REQUEST_OF_NUMBER_OF_USERS_IN_MATCH:
            sendResponseToRequestOfNumberOfUsersInMatch(messageReceived);
            break;
        case REQUEST_OF_START_MATCH:
            sendResponseToRequestOfStartMatch(messageReceived);
            break;
        default:
            throw Exception("Invalid message from client");
            break;
    }
}
