#ifndef EDITOR_MENUWINDOW_H
#define EDITOR_MENUWINDOW_H

#include "ScreenManager.h"
#include <QMainWindow>
#include <QWidget>

namespace Ui {
    class MenuWindow;
}

class MenuWindow : public QMainWindow {
    Q_OBJECT;

    private:
        Ui::MenuWindow *ui;
        ScreenManager *screenManager;

    public:
        MenuWindow(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~MenuWindow();

    private:
        void nextScreen();
        void connectEvents();
        void setStyle();

};

#endif //EDITOR_MENUWINDOW_H
