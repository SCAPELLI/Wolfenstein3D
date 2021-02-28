#include <vector>
#include <common/include/Protocol.h>
#include "client/include/CommunicationChannelClient.h"
#include "common/include/Exception.h"
#include "common/include/Socket.h"
#include "common/include/MatchInfo.h"

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

void CommunicationChannelClient::addZerosToLeft(std::string &string, int finalSize) {
    if (string.length() > finalSize)
        throw Exception("the message '" + string + "' is to long, cannot add zeros to left");
    while (string.length() < finalSize)
        string.insert(string.begin(), '0');
}

CommunicationChannelClient::CommunicationChannelClient(Socket& socket): socket(socket) {}

void CommunicationChannelClient::sendUserNameSubmit(std::string userName) {
    Protocol protocol(&socket);
    protocol.send(USER_NAME_SUBMIT_STRING + userName);
}

void CommunicationChannelClient::sendRequestOfAvailableMatches() {
    Protocol protocol(&socket);
    protocol.send(REQUEST_OF_MATCHES_STRING);
}

void CommunicationChannelClient::sendRequestOfMatchCreation(int level, int maximumNumberOfPlayers, int userId) {
    str levelString = std::to_string(level);
    addZerosToLeft(levelString, 3);

    str userIdString = std::to_string(userId);
    addZerosToLeft(userIdString, 3);

    str maximumPlayersString = std::to_string(maximumNumberOfPlayers);
    addZerosToLeft(maximumPlayersString, 3);

    Protocol protocol(&socket);
    protocol.send(REQUEST_OF_MATCH_CREATION_STRING + levelString + userIdString + maximumPlayersString);
}

void CommunicationChannelClient::sendRequestOfMatchCancellation(int matchId) {
    Protocol protocol(&socket);
    protocol.send(REQUEST_OF_MATCH_CANCELLATION_STRING + std::to_string(matchId));
}

void CommunicationChannelClient::sendRequestOfJoiningAMatch(int matchId, int userId) {
    str matchIdString = std::to_string(matchId);
    addZerosToLeft(matchIdString, 3);

    str userIdString = std::to_string(userId);
    addZerosToLeft(userIdString, 3);

    Protocol protocol(&socket);
    protocol.send(REQUEST_OF_JOINING_A_MATCH_STRING + matchIdString + userIdString);
}

void CommunicationChannelClient::sendRequestOfNumberOfUsersInMatch(int matchId) {
    str matchIdString = std::to_string(matchId);

    Protocol protocol(&socket);
    protocol.send(REQUEST_OF_NUMBER_OF_USERS_IN_MATCH_STRING + matchIdString);
}

void CommunicationChannelClient::sendRequestOfStartMatch(int matchId) {
    str matchIdString = std::to_string(matchId);
    Protocol protocol(&socket);
    protocol.send(REQUEST_OF_START_MATCH_STRING + matchIdString);
}

int CommunicationChannelClient::receiveClientIdFromServer() {
    str messageReceived;
    Protocol protocol(&socket);
    protocol.receive(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode ==  USER_NAME_SUCCESSFULLY_SUBMITTED)
        return std::stoi(messageReceived.substr(3));
    if (messageReceived == INVALID_USER_NAME_STRING)
        return -1;
    throw Exception("Message not expected");
}

std::vector<MatchInfo> CommunicationChannelClient::getMatches(str messageReceived) {
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

std::vector<MatchInfo> CommunicationChannelClient::receiveListOfMatches() {
    str messageReceived;
    Protocol protocol(&socket);
    protocol.receive(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode != LIST_OF_MATCHES)
        throw Exception("Message not expected");
    return getMatches(messageReceived);
}

int CommunicationChannelClient::receiveResponseToRequestOfMatchCreation() {
    str messageReceived;
    Protocol protocol(&socket);
    protocol.receive(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode == MATCH_CREATED_SUCCESSFULLY)
        return std::stoi(messageReceived.substr(3, 3));
    if (messageCode == MATCH_NOT_CREATED)
        return -1;
    throw Exception("Message not expected");
}

int CommunicationChannelClient::receiveResponseOfJoiningAMatch() {
    str messageReceived;
    Protocol protocol(&socket);
    protocol.receive(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode == MATCH_STARTED_SIGNAL)
        return 0;
    if (messageCode == FAILED_TO_JOIN_TO_MATCH)
        return -1;
    throw Exception("Message not expected");
}
int CommunicationChannelClient::receiveResponseOfMatchCancellation() {
    str messageReceived;
    Protocol protocol(&socket);
    protocol.receive(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode == MATCH_CANCELLED_SUCCESSFULLY)
        return 0;
    if (messageCode == MATCH_NOT_CANCELLED)
        return -1;
    throw Exception("Message not expected");
}
int CommunicationChannelClient::receiveResponseOfNumberOfMatches() {
    str messageReceived;
    Protocol protocol(&socket);
    protocol.receive(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));
    if (messageCode == SUCCESSFULLY_GOT_THE_NUMBER_OF_USERS_IN_MATCH)
        return std::stoi(messageReceived.substr(3));
    if (messageCode == FAILED_TO_GET_THE_NUMBER_OF_USERS_IN_MATCH)
        return -1;
    throw Exception("Message not expected");
}
int CommunicationChannelClient::receiveResponseToRequestOfStartMatch() {
    str messageReceived;
    Protocol protocol(&socket);
    protocol.receive(messageReceived);
    if (messageReceived.empty()) throw Exception("Server not available");

    int messageCode = std::stoi(messageReceived.substr(0, 3));

    if (messageCode == MATCH_NOT_STARTED)
        return -1;
    if(messageCode == MATCH_STARTED_SIGNAL)
        return 0;
    throw Exception("Message not excepted");
}