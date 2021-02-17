#include "../../common/include/Socket.h"
#include "../include/TCPClient.h"
#include "../../common/include/ProtectedLobby.h"
#include "../../common/include/CommunicationChannel.h"

void printListOfMatches(std::vector<MatchInfo> matches) {
    std::cout<<"--------------------"<<std::endl;
    std::cout<<"List of matches available"<<std::endl<<std::endl;
    for (MatchInfo& match: matches) {
        std::cout << "matchId " << match.getMatchId()<<" | ";
        std::cout << "level " << match.getLevelId()<<" | ";
        std::cout << "Users " << match.getActualNumberOfUsers()<<"/"<<match.getMaximumNumberOfUsers()<<std::endl;
    }
    std::cout<<"--------------------"<<std::endl;
}
void failedToCreatedMatchMenu(bool& exitMatchCreationMenu) {
    std::cout << "Failed to created match" << std::endl;
    int response = 0;
    while (response != 1 and response != 2) {
        std::cout << "1--try again" << std::endl;
        std::cout << "2--exit" << std::endl;
        std::cin >> response;

        switch (response) {
            case 1:
            break;
            case 2:
                exitMatchCreationMenu = true;
            break;
            default:
                std::cout<<"Invalid option"<<std::endl;
            break;
        }
    }
}

void playMatch(CommunicationChannel& channel, int userId, Socket& userSocket, int matchId) {
    //codigo de separacion de threads etc.
}

void startCreatedMatchMenu(CommunicationChannel& channel,
                           int adminUserId, Socket& userSocket,int matchId, int maximumNumberOfUsers) {

    std::cout<<"Match successfully created"<<std::endl;

    int numberOfUsersInMatch = 1;
    int response = 0;
    while (response != 1 and response != 2) {
        std::cout<<"Number of users connected: "<<numberOfUsersInMatch<<"/"<<maximumNumberOfUsers<<std::endl;
        std::cout<<"1--start match"<<std::endl;
        std::cout<<"2--cancel match"<<std::endl;
        std::cout<<"3--refresh users in match"<<std::endl;

        std::cin >> response;
        switch (response) {
            case 1:
                channel.sendRequestOfStartMatch(matchId);
                if (channel.receiveResponseToRequestOfStartMatch() != -1)
                    playMatch(channel, matchId, userSocket, matchId);
                break;
            case 2:
                channel.sendRequestOfMatchCancellation(matchId);
                channel.receiveResponseOfMatchCancellation();
                break;
            case 3:
                channel.sendRequestOfNumberOfUsersInMatch(matchId);
                numberOfUsersInMatch = channel.receiveResponseOfNumberOfMatches();
            default:
                std::cout<<"Invalid option"<<std::endl;
                break;
        }
    }
}

void matchCreationMenu(CommunicationChannel& channel, int adminUserId, Socket& userSocket) {
    bool exitMatchCreationMenu = false;
    while (!exitMatchCreationMenu) {
        int levelId;

        std::cout<<"Level: "; std::cin>>levelId;
        int maximumNumberOfUsers;
        std::cout<<"Maximum number of users: "; std::cin>>maximumNumberOfUsers;

        channel.sendRequestOfMatchCreation(levelId, maximumNumberOfUsers, adminUserId);
        int matchId = channel.receiveResponseToRequestOfMatchCreation();

        if (matchId == -1) {
            failedToCreatedMatchMenu(exitMatchCreationMenu);
        } else {
            startCreatedMatchMenu(channel, adminUserId, userSocket, matchId, maximumNumberOfUsers);
            exitMatchCreationMenu = true;
        }

    }
}

void matchJoiningMenu(CommunicationChannel& channel, int userId, Socket& userSocket) {

    std::cout<<"matchId: ";
    int matchId;
    std::cin>>matchId;
    std::cout<<"connecting..."<<std::endl;
    channel.sendRequestOfJoiningAMatch(matchId, userId);
    int response = channel.receiveResponseOfJoiningAMatch();
    if (response == -1)
        std::cout<<"failed to connect"<<std::endl;
    else
        playMatch(channel, userId, userSocket, matchId);
}

int main() {
    try {
        const char* dominio = "localhost";
        const char* puerto = "7777";

        Socket userSocket;
        userSocket = std::move(TCPClient::getClientSocket(dominio, puerto));
        ProtectedLobby lobby;
        CommunicationChannel channel(userSocket, lobby);

        int userId = -1;
        std::string userName;
        while (userId == -1) {
            std::cout<<"User name: ";
            std::cin>>userName;
            channel.sendUserNameSubmit(userName);
            userId = channel.receiveClientIdFromServer();
            if (userId == -1) std::cout<<"Invalid user name"<<std::endl;
        }
//----------------------------------

        channel.sendRequestOfAvailableMatches();
        std::vector<MatchInfo> matches = channel.receiveListOfMatches();

        bool quit = false;
        while (!quit) {
            std::cout<<"\n\n";
            printListOfMatches(matches);
            std::cout<<"Options"<<std::endl<<std::endl;
            std::cout<<"1--create a match"<<std::endl;
            std::cout<<"2--join a match"<<std::endl;
            std::cout<<"3--refresh"<<std::endl;
            std::cout<<"4--exit"<<std::endl<<std::endl;

            int option;
            std::cin >> option;
            switch (option) {
                case 1:
                    matchCreationMenu(channel, userId, userSocket);
                    channel.sendRequestOfAvailableMatches();
                    matches = channel.receiveListOfMatches();
                    break;
                case 2:
                    matchJoiningMenu(channel, userId, userSocket);
                    channel.sendRequestOfAvailableMatches();
                    matches = channel.receiveListOfMatches();
                    break;
                case 3:
                    channel.sendRequestOfAvailableMatches();
                    matches = channel.receiveListOfMatches();
                    break;
                case 4:
                    quit = true;
                    break;
                default:
                    std::cout<<"Invalid option"<<std::endl;
                    break;
            }
        }
        //channel.sendRequestOfMatchCreation(1, 54, urchesId);
        //int matchId = channel.receiveResponseToRequestOfMatchCreation();

        //int matchId = matches1.back().getMatchId();

        //channel.sendRequestOfJoiningAMatch(matchId, carpinchoId);
        //int response1 = channel.receiveResponseOfJoiningAMatch();

        //channel.sendRequestOfNumberOfUsersInMatch(matchId);
        //int response2 = channel.receiveResponseOfNumberOfMatches();

        //channel.sendRequestOfMatchCancellation(matchId);
        //int response3 = channel.receiveResponseOfMatchCancellation();

        //channel.sendRequestOfAvailableMatches();
        //std::vector<MatchInfo> matches2 = channel.receiveListOfMatches();

        //std::cout<<"ingresar x para empezar la partida: "<<std::endl;
        //char entrada = ' ';
        //while (entrada!='x') std::cin >> entrada;

        //channel.sendRequestOfStartMatch(matchId);
        //int response4 = channel.receiveResponseToRequestOfStartMatch();

        userSocket.doClose();
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
