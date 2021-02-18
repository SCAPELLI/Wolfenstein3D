#include "../include/UserThread.h"
#include "../include/CommunicationChannel.h"
#include "../include/Socket.h"

UserThread::UserThread(Socket& user, ProtectedLobby& lobby):
        user(user), lobby(lobby), runFinished(false) {}

void UserThread::run() {
    CommunicationChannel channel(user, lobby);
    int userId = -1;

    while (userId == -1)
        userId = channel.respondUserNameSubmitFromClient();

    while (user.isAvailable())
        channel.respondMessageFromClient(userId);

    user.doClose();
}
