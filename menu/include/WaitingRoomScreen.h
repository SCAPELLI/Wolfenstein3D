#ifndef MENU_WAITINGROOMSCREEN_H
#define MENU_WAITINGROOMSCREEN_H


#include <QtWidgets/QWidget>
#include "ScreenManager.h"

namespace Ui {
    class WaitingRoomScreen;
}

class WaitingRoomScreen: public QWidget {
    Q_OBJECT;

    private:
        Ui::WaitingRoomScreen *ui;
        ScreenManager *screenManager;
        void connectEvents();
        void onStartButtonClick();
        void onRefreshButtonClick();
        void onCancelButtonClick();

    public:
        WaitingRoomScreen(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~WaitingRoomScreen();
        void refresh();

};


#endif //MENU_WAITINGROOMSCREEN_H
