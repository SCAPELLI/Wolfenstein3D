#include <iostream>
#include "Client.h"

Client::Client() {

}

Client::~Client() {

}

bool Client::tryToConnect(std::string port, std::string domain) {
    // Conectarse

    std::cout << "Port: " << port << "\n";
    std::cout << "Domain: " << domain << "\n";

    return true;
}

bool Client::tryToSubmitUsername(std::string nickname) {
    // Cosas

    std::cout << "Username: " << nickname << "\n";

    return true;
}

bool Client::tryToJoin(int matchId) {
    // COSAS

    std::cout << "matchId:" << matchId << "\n";

    return true;
}

std::vector<MatchInfo> Client::requestMatches() {
    MatchInfo match1(6, 1, 30, 8);

    MatchInfo match2(7, 2, 55, 2);

    MatchInfo match3(8, 3, 5, 1);

    std::vector<MatchInfo> matches = {match1, match2, match3};
    return matches;
}

bool Client::tryToCreateAMatch(int level, int maxPlayer) {
    // COSAS
    std::cout << "Level:" << level << "\n";
    std::cout << "Max players:" << maxPlayer << "\n";
    return true;
}

int Client::getLevel() {
    // COSAS
    return 9999;
}

int Client::getActualPlayers() {
    // Cosas
    return 666;
}

int Client::getMaxPlayers() {
    return 42;
}

