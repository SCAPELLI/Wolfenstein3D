#include "../include/UserThread.h"
#include "../../server/include/CommunicationChannelServer.h"
#include "../../common/include/Socket.h"

UserThread::UserThread(Socket& user, ProtectedLobby& lobby):
        user(user), lobby(lobby), runFinished(false) {}

void UserThread::run() {
    try {
	    CommunicationChannelServer channel(user, lobby);
	    int userId = -1;

	    while (userId == -1)
	        userId = channel.respondUserNameSubmitFromClient();

	    while (user.isAvailable())
		        channel.respondMessageFromClient(userId);
		
		user.doClose();
	} catch(...) {}
}