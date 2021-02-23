#include <iostream>
#include "client/include/Client.h"
#include "client/include/TCPClient.h"
#include "client/include/CommunicationChannelClient.h"

Client::Client() {
    channel = new CommunicationChannelClient(userSocket);
    userId = -1;
    matchId = -1;
    maximumNumberOfPlayers = -1;
    levelId = -1;
}
Client::~Client() {
    delete channel;
}

bool Client::tryToConnect(std::string port, std::string domain) {
    try {
        userSocket = std::move(TCPClient::getClientSocket("localhost", "7777"));
        return true;
    } catch (const std::exception& error) {
        return false;
    }
}

bool Client::tryToSubmitUsername(std::string userName) {

    channel->sendUserNameSubmit(userName);
    userId = channel->receiveClientIdFromServer();
    if (userId == -1) return false;
    else return true;
}

bool Client::tryToJoin(int matchId) {
    channel->sendRequestOfJoiningAMatch(matchId, userId);
    int response = channel->receiveResponseOfJoiningAMatch();
    if (response == -1) {
        return false;
    } else {
        playMatch();
        return true;
    }
}

std::vector<MatchInfo> Client::requestMatches() {
    channel->sendRequestOfAvailableMatches();
    std::vector<MatchInfo> matches = channel->receiveListOfMatches();

    return matches;
}

bool Client::tryToCreateAMatch(int level, int maxPlayer) {
    levelId = level;
    maximumNumberOfPlayers = maxPlayer;
    if (maximumNumberOfPlayers>999) return false;
    channel->sendRequestOfMatchCreation(level, maxPlayer, userId);
    matchId = channel->receiveResponseToRequestOfMatchCreation();
    if (matchId == -1) return false;
    else return true;
}

int Client::getLevel() {
    return levelId;
}

int Client::getActualPlayers() {
    channel->sendRequestOfNumberOfUsersInMatch(matchId);
    return channel->receiveResponseOfNumberOfMatches();
}

int Client::getMaxPlayers() {
    return maximumNumberOfPlayers;
}

bool Client::tryToCancelMatch() {
    channel->sendRequestOfMatchCancellation(matchId);
    int response = channel->receiveResponseOfMatchCancellation();
    if (response == -1) {
        return false;
    } else {
        maximumNumberOfPlayers = -1;
        levelId = -1;
        return true;
    }
}
bool Client::tryToStartMatch() {
    channel->sendRequestOfStartMatch(matchId);
    if (channel->receiveResponseToRequestOfStartMatch() != -1) {
        playMatch();
        return true;
    } else {
        return false;
    }
}
void Client::playMatch() {
    //codigo de separacion de threads etc.
}