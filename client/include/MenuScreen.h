#ifndef MENU_MENUSCREEN_H
#define MENU_MENUSCREEN_H


#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>

namespace Ui {
    class MenuScreen;
}

class MenuScreen : public QMainWindow {
    private:
        Ui::MenuScreen *ui;
        QStackedWidget *stack;
        QString actualBackgroundNameFile;

    public:
        MenuScreen(QWidget *parent = 0);
        ~MenuScreen();
        void connectEvents();
        void setMenuBackground();
        void setNicknameBackground();
        void changeToNicknameScreen();
        void changeToMenuScreen();
        void resizeEvent(QResizeEvent *event);
        void setButtonStyle();
        void acceptButtonEvent();
        void cancelButtonEvent();
};


#endif //MENU_MENUSCREEN_H
