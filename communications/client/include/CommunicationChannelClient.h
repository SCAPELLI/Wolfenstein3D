#ifndef COMMUNICATIONCHANNELCLIENT_H
#define COMMUNICATIONCHANNELCLIENT_H

#include <string>

typedef std::string str;

class Socket;
class MatchInfo;

class CommunicationChannelClient {
    Socket &socket;

    void addZerosToLeft(str &string, int finalSize);
    std::vector<MatchInfo> getMatches(str messageReceived);
public:

    explicit CommunicationChannelClient(Socket& socket);
    void sendUserNameSubmit(str userName);

    int receiveClientIdFromServer();
    void sendRequestOfAvailableMatches();
    std::vector<MatchInfo> receiveListOfMatches();

    void sendRequestOfMatchCreation(int level, int maximumNumberOfPlayers, int userId);
    int receiveResponseToRequestOfMatchCreation();

    void sendRequestOfStartMatch(int matchId);
    int receiveResponseToRequestOfStartMatch();

    void sendRequestOfMatchCancellation(int matchId);
    int receiveResponseOfMatchCancellation();

    void sendRequestOfJoiningAMatch(int matchId, int userId);
    int receiveResponseOfJoiningAMatch();

    void sendRequestOfNumberOfUsersInMatch(int matchId);
    int receiveResponseOfNumberOfMatches();
};


#endif
