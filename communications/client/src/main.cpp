#include "../../common/include/Socket.h"
#include "../include/TCPClient.h"
#include "../../common/include/ProtectedLobby.h"
#include "../../common/include/CommunicationChannel.h"

int main() {
    try {
        char* dominio = "localhost";
        char* puerto = "7777";

        Socket client;
        client = std::move(TCPClient::getClientSocket(dominio, puerto));
        ProtectedLobby lobby;
        CommunicationChannel channel(client, lobby);

        channel.sendUserNameSubmit("Urches");
        int urchesId = channel.receiveClientIdFromServer();

        //channel.sendUserNameSubmit("asd");
        //int carpinchoId = channel.reciveClientIdFromServer();
//----------------------------------
        channel.sendRequestOfMatchCreation(1, 54, urchesId);
        int matchId = channel.receiveResponseToRequestOfMatchCreation();

        //channel.sendRequestOfJoiningAMatch(matchId, carpinchoId);
        //int response1 = channel.reciveRespondOfJoiningAMatch();

        channel.sendRequestOfAvailableMatches();
        std::vector<MatchInfo> matches1 = channel.receiveListOfMatches();

        channel.sendRequestOfNumberOfUsersInMatch(matchId);
        int response2 = channel.receiveResponseOfNumberOfMatches();

        //channel.sendRequestOfMatchCancellation(matchId);
        //int response3 = channel.receiveResponseOfMatchCancellation();

        channel.sendRequestOfAvailableMatches();
        std::vector<MatchInfo> matches2 = channel.receiveListOfMatches();

        channel.sendRequestOfStartMatch(matchId);
        int response4 = channel.receiveResponseToRequestOfStartMatch();

        client.doClose();
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
