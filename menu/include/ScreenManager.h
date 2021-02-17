#ifndef MENU_SCREENMANAGER_H
#define MENU_SCREENMANAGER_H


#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include "Client.h"

class WaitingRoomScreen;

namespace Ui {
    class ScreenManager;
}

class ScreenManager: public QMainWindow {
    Q_OBJECT;

    private:
        Ui::ScreenManager *ui;
        QStackedWidget *screens;
        Client *client;
        WaitingRoomScreen *waitingRoomScreen;

    public:
        ScreenManager(QWidget *parent = 0);
        ~ScreenManager();
        void goNext();
        void goBack();

        bool tryToConnect(std::string port, std::string domain);
        bool tryToSubmitUsername(std::string nickname);
        bool tryToJoin(int matchId);
        std::vector<MatchInfo> requestMatches();
        bool tryToCreateAMatch(int level, int maxPlayer);
        int getLevel();
        int getActualPlayers();
        int getMaxPlayers();
        void refreshWaitingRoom();
};


#endif //MENU_SCREENMANAGER_H
