#ifndef MENU_GAMESSCREEN_H
#define MENU_GAMESSCREEN_H


#include <QtWidgets/QWidget>
#include "ScreenManager.h"
#include "../../common/MatchInfo.h"


namespace Ui {
    class GamesScreen;
}

class GamesScreen: public QWidget {
    Q_OBJECT;

    private:
        Ui::GamesScreen *ui;
        ScreenManager *screenManager;
        std::vector<int> idMatches;

    private:
        void setDataTable();
        void setStyle();
        void onJoinButtonClick();
        void onRefreshButtonClick();
        void clearTable();

    public:
        GamesScreen(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~GamesScreen();
        void connectEvents();
        void addMatch(MatchInfo match);
};


#endif //MENU_GAMESSCREEN_H