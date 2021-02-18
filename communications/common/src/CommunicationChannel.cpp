#include "../include/CommunicationChannel.h"
#include "../include/Exception.h"
#include "../include/Match.h"
#include "../include/ProtectedLobby.h"
#include "../include/Socket.h"

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

void CommunicationChannel::addZerosToLeft(std::string &string, int finalSize) {
    if (string.length() > finalSize)
        throw Exception("the message '" + string + "' is to long, cannot add zeros to left");
    while (string.length() < finalSize)
        string.insert(string.begin(), '0');
}

CommunicationChannel::CommunicationChannel(Socket& socket, ProtectedLobby& lobby): socket(socket), lobby(lobby){}

void CommunicationChannel::sendUserNameSubmit(std::string userName) {
    socket.sendAll(USER_NAME_SUBMIT_STRING + userName);
}

int CommunicationChannel::sendResponseToUserNameSubmit(str &messageReceived) {
    str userName = messageReceived.substr(3);
    int userId = lobby.addUser(userName);
    if (userId != -1)
        socket.sendAll(USER_NAME_SUCCESSFULLY_SUBMITTED_STRING + std::to_string(userId));
    else
        socket.sendAll(INVALID_USER_NAME_STRING);
    return userId;
}

void CommunicationChannel::sendRequestOfAvailableMatches() {
    socket.sendAll(REQUEST_OF_MATCHES_STRING);
}

void CommunicationChannel::sendResponseToRequestOfMatches() {
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

void CommunicationChannel::sendRequestOfMatchCreation(int level, int maximumNumberOfPlayers, int userId) {
    str levelString = std::to_string(level);
    addZerosToLeft(levelString, 3);

    str maximumPlayersString = std::to_string(maximumNumberOfPlayers);
    addZerosToLeft(maximumPlayersString, 3);

    str userIdString = std::to_string(userId);
    addZerosToLeft(userIdString, 3);

    socket.sendAll(REQUEST_OF_MATCH_CREATION_STRING + levelString + maximumPlayersString + userIdString);
}

void CommunicationChannel::sendResponseToRequestOfMatchCreation(str &messageReceived) {
    int levelId = std::stoi(messageReceived.substr(3, 3));
    int maximumNumberOfPlayers = std::stoi(messageReceived.substr(6, 3));
    int userId = std::stoi(messageReceived.substr(9,3));

    int matchId = lobby.createANewMatch(levelId, maximumNumberOfPlayers, userId, &socket);
    if (matchId == -1) {
        socket.sendAll(MATCH_NOT_CREATED_STRING);
    } else {
        str matchIdString = std::to_string(matchId);
        addZerosToLeft(matchIdString, 3);
        socket.sendAll(MATCH_CREATED_SUCCESSFULLY_STRING + matchIdString);
    }
}

void CommunicationChannel::sendRequestOfMatchCancellation(int matchId) {
    socket.sendAll(REQUEST_OF_MATCH_CANCELLATION_STRING + std::to_string(matchId));
}

void CommunicationChannel::sendResponseToRequestOfMatchCancellation(str &messageReceived) {
    int matchId = std::stoi(messageReceived.substr(3));
    int response = lobby.cancelMatch(matchId);

    if (response == -1)
        socket.sendAll(MATCH_NOT_CANCELLED_STRING);
    else
        socket.sendAll(MATCH_CANCELLED_SUCCESSFULLY_STRING);
}

void CommunicationChannel::sendRequestOfJoiningAMatch(int matchId, int userId) {
    str matchIdString = std::to_string(matchId);
    addZerosToLeft(matchIdString, 3);

    str userIdString = std::to_string(userId);
    addZerosToLeft(userIdString, 3);

    socket.sendAll(REQUEST_OF_JOINING_A_MATCH_STRING + matchIdString + userIdString);
}

void CommunicationChannel::sendResponseToRequestOfJoiningAMatch(str &messageReceived) {
    int matchId = std::stoi(messageReceived.substr(3, 3));
    int userId = std::stoi(messageReceived.substr(6, 3));

    int response = lobby.addUserToMatch(matchId, userId, &socket);
    if (response == -1)
        socket.sendAll(FAILED_TO_JOIN_TO_MATCH_STRING);
}
void CommunicationChannel::sendRequestOfNumberOfUsersInMatch(int matchId) {
    str matchIdString = std::to_string(matchId);
    socket.sendAll(REQUEST_OF_NUMBER_OF_USERS_IN_MATCH_STRING + matchIdString);
}
void CommunicationChannel::sendResponseToRequestOfNumberOfUsersInMatch(str& messageReceived) {
    int matchId = std::stoi(messageReceived.substr(3));
    int response = lobby.numberOfUsersInMatch(matchId);
    if (response == -1)
        socket.sendAll(FAILED_TO_GET_THE_NUMBER_OF_USERS_IN_MATCH_STRING);
    else
        socket.sendAll(SUCCESSFULLY_GOT_THE_NUMBER_OF_USERS_IN_MATCH_STRING + std::to_string(response));
}

void CommunicationChannel::sendRequestOfStartMatch(int matchId) {
    str matchIdString = std::to_string(matchId);
    socket.sendAll(REQUEST_OF_START_MATCH_STRING + matchIdString);
}

void CommunicationChannel::sendResponseToRequestOfStartMatch(str& messageReceived) {
    int matchId = std::stoi(messageReceived.substr(3));

    int response = lobby.startMatch(matchId);

    if (response == -1)
        socket.sendAll(MATCH_NOT_STARTED_STRING);
}

void CommunicationChannel::sendMatchStartedSignal(Socket* socket) {
    socket->sendAll(MATCH_STARTED_SIGNAL_STRING);
}

int CommunicationChannel::respondUserNameSubmitFromClient() {
    str messageReceived;
    socket.reciveAll(messageReceived);
    if (!socket.isAvailable()) return -1;

    int messageCode = std::stoi(messageReceived.substr(0, 3));

    if (messageCode != USER_NAME_SUBMIT)
        throw Exception("User Submit Expected");
    return sendResponseToUserNameSubmit(messageReceived);
}

void CommunicationChannel::respondMessageFromClient(int userId) {
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
int CommunicationChannel::receiveClientIdFromServer() {
    str messageReceived;
    socket.reciveAll(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode ==  USER_NAME_SUCCESSFULLY_SUBMITTED)
        return std::stoi(messageReceived.substr(3));
    if (messageReceived == INVALID_USER_NAME_STRING)
        return -1;
    throw Exception("Message not expected");
}

std::vector<MatchInfo> CommunicationChannel::getMatches(str messageReceived) {
    int numberOfMatches = std::stoi(messageReceived.substr(3, 3));
    str matchesInfo = messageReceived.substr(6);

    std::vector<MatchInfo> matches;

    if (matchesInfo.size() != (numberOfMatches * 12))
        throw Exception("Invalid list of matches");
    for (int matchNumber = 0; matchNumber < numberOfMatches; ++matchNumber) {
        int matchId = std::stoi(matchesInfo.substr((matchNumber * 12) + 0, 3));
        int levelId = std::stoi(matchesInfo.substr((matchNumber * 12) + 3, 3));
        int maximumNumberOfPlayers = std::stoi(matchesInfo.substr((matchNumber * 12) + 6, 3));
        int actualNumberOfPlayers = std::stoi(matchesInfo.substr((matchNumber * 12) + 9, 3));
        matches.emplace_back(matchId, levelId, maximumNumberOfPlayers, actualNumberOfPlayers);
    }
    return matches;
}

std::vector<MatchInfo> CommunicationChannel::receiveListOfMatches() {
    str messageReceived;
    socket.reciveAll(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode != LIST_OF_MATCHES)
        throw Exception("Message not expected");
    return getMatches(messageReceived);
}

int CommunicationChannel::receiveResponseToRequestOfMatchCreation() {
    str messageReceived;
    socket.reciveAll(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode == MATCH_CREATED_SUCCESSFULLY)
        return std::stoi(messageReceived.substr(3, 3));
    if (messageCode == MATCH_NOT_CREATED)
        return -1;
    throw Exception("Message not expected");
}

int CommunicationChannel::receiveResponseOfJoiningAMatch() {
    str messageReceived;
    socket.reciveAll(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode == MATCH_STARTED_SIGNAL)
        return 0;
    if (messageCode == FAILED_TO_JOIN_TO_MATCH)
        return -1;
    throw Exception("Message not expected");
}
int CommunicationChannel::receiveResponseOfMatchCancellation() {
    str messageReceived;
    socket.reciveAll(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode == MATCH_CANCELLED_SUCCESSFULLY)
        return 0;
    if (messageCode == MATCH_NOT_CANCELLED)
        return -1;
    throw Exception("Message not expected");
}
int CommunicationChannel::receiveResponseOfNumberOfMatches() {
    str messageReceived;
    socket.reciveAll(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode == SUCCESSFULLY_GOT_THE_NUMBER_OF_USERS_IN_MATCH)
        return std::stoi(messageReceived.substr(3));
    if (messageCode == FAILED_TO_GET_THE_NUMBER_OF_USERS_IN_MATCH)
        return -1;
    throw Exception("Message not expected");
}
int CommunicationChannel::receiveResponseToRequestOfStartMatch() {
    str messageReceived;
    socket.reciveAll(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));

    if (messageCode == MATCH_NOT_STARTED)
        return -1;
    if(messageCode == MATCH_STARTED_SIGNAL)
        return 0;
    throw Exception("Message not excepted");
}
