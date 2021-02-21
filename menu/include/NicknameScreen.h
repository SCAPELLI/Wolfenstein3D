#ifndef MENU_NICKNAMESCREEN_H
#define MENU_NICKNAMESCREEN_H


#include <QtWidgets/QWidget>
#include "ScreenManager.h"

namespace Ui {
    class NicknameScreen;
}

class NicknameScreen : public QWidget {
    Q_OBJECT;

    private:
        Ui::NicknameScreen *ui;
        ScreenManager *screenManager;

    private:
        void setStyle();
        void connectEvents();
        void onAcceptButtonClick();
        void onCancelButtonClick();

    public:
        NicknameScreen(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~NicknameScreen();

};


#endif //MENU_NICKNAMESCREEN_H
