#ifndef MENU_SCREENMANAGER_H
#define MENU_SCREENMANAGER_H


#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>

namespace Ui {
    class ScreenManager;
}

class ScreenManager: public QMainWindow {
    Q_OBJECT;

    private:
        Ui::ScreenManager *ui;
        QStackedWidget *screens;

    public:
        ScreenManager(QWidget *parent = 0);
        ~ScreenManager();
};


#endif //MENU_SCREENMANAGER_H
