#ifndef MENU_INFOSCREEN_H
#define MENU_INFOSCREEN_H


#include <QtWidgets/QWidget>
#include "ScreenManager.h"

namespace Ui {
    class InfoScreen;
}

class InfoScreen: public QWidget {
    Q_OBJECT;

    private:
        Ui::InfoScreen *ui;
        ScreenManager *screenManager;

    private:
        void connectEvents();
        void onAcceptButtonClick();
        void onCancelButtonClick();

    public:
        InfoScreen(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~InfoScreen();
};


#endif //MENU_INFOSCREEN_H
