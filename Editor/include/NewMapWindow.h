#ifndef EDITOR_NEWMAPWINDOW_H
#define EDITOR_NEWMAPWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "ScreenManager.h"

namespace Ui {
    class NewMapWindow;
}

class NewMapWindow : public QMainWindow {
    Q_OBJECT

    private:
        Ui::NewMapWindow *ui;
        ScreenManager *screenManager;

    public:
        NewMapWindow(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~NewMapWindow();

    private:
        void connectEvents();
        void createMap();
        void previousScreen();
        void nextScreen();
};

#endif //EDITOR_NEWMAPWINDOW_H
