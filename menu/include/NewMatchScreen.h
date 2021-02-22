#ifndef MENU_NEWMATCHSCREEN_H
#define MENU_NEWMATCHSCREEN_H

#include <QtWidgets/QWidget>
#include "ScreenManager.h"

namespace Ui {
    class NewMatchScreen;
}

class NewMatchScreen: public QWidget {
    private:
        Ui::NewMatchScreen *ui;
        ScreenManager *screenManager;

    private:
        void setOptions();
        void connectEvents();
        void onAcceptButtonClick();
        void onCancelButtonClick();
        void setStyle();

    public:
        NewMatchScreen(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~NewMatchScreen();
};


#endif //MENU_NEWMATCHSCREEN_H
