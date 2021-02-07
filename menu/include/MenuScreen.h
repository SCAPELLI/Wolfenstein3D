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
        void setBackground();
        void resizeEvent(QResizeEvent *event);
        void setButtonStyle();
};


#endif //MENU_MENUSCREEN_H
