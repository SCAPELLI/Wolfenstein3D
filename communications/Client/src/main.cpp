#include "../include/Socket.h"
#include "../include/TCPClient.h"
#include "../include/ProtectedLobby.h"
#include "../include/CommunicationChannel.h"

int main() {
    try {
        char* dominio = "localhost";
        char* puerto = "7777";

        Socket client;
        client = std::move(TCPClient::getClientSocket(dominio, puerto));
        ProtectedLobby lobby;
        CommunicationChannel channel(client, lobby);

        channel.sendUserNameSubmit("Urches");
        int urchesId = channel.reciveClientIdFromServer();

        channel.sendUserNameSubmit("srCarpincho");
        int carpinchoId = channel.reciveClientIdFromServer();
//----------------------------------
        channel.sendRequestOfMatchCreation(1, 54, urchesId);
        int matchId = channel.reciveRespondToRequestOfMatchCreation();

        channel.sendRequestOfJoiningAMatch(matchId, carpinchoId);
        int response1 = channel.reciveRespondOfJoiningAMatch();

        channel.sendRequestOfAvailableMatches();
        std::vector<MatchInfo> matches1 = channel.reciveListOfMatches();

        channel.sendRequestOfNumberOfUsersInMatch(matchId);
        int response2 = channel.reciveRespondOfNumberOfMatches();

        channel.sendRequestOfMatchCancellation(matchId);
        int response3 = channel.reciveRespondOfMatchCancellation();

        channel.sendRequestOfAvailableMatches();
        std::vector<MatchInfo> matches2 = channel.reciveListOfMatches();


        client.doClose();
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
