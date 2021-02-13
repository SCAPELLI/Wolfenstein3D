#ifndef MENU_STARTSCREEN_H
#define MENU_STARTSCREEN_H


#include "ScreenManager.h"

namespace Ui {
    class StartScreen;
}

class StartScreen: public QWidget {
    Q_OBJECT;

    private:
        Ui::StartScreen *ui;
        ScreenManager *screenManager;

    private:
        void paintEvent(QPaintEvent *e);
        void setStyle();

    public:
        StartScreen(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~StartScreen();
};


#endif //MENU_STARTSCREEN_H
