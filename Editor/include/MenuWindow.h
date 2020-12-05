#ifndef EDITOR_MENUWINDOW_H
#define EDITOR_MENUWINDOW_H

#include "../include/NewMapWindow.h"
#include "SceneManager.h"
#include <QMainWindow>
#include <QWidget>

namespace Ui {
    class MenuWindow;
}

class MenuWindow : public QMainWindow {
    Q_OBJECT;

    private:
        Ui::MenuWindow *ui;
        //NewMapWindow *newMapWindow;
        SceneManager *sceneManager;

    public:
        MenuWindow(QWidget *parent = 0, SceneManager *sceneManager = NULL);
        ~MenuWindow();

    private:
        void openCreateMapWindow();
        void connectEvents();

};


#endif //EDITOR_MENUWINDOW_H
