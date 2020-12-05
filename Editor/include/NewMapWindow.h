#ifndef EDITOR_NEWMAPWINDOW_H
#define EDITOR_NEWMAPWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "SceneManager.h"

namespace Ui {
    class NewMapWindow;
}

class NewMapWindow : public QMainWindow {
    Q_OBJECT

    private:
        Ui::NewMapWindow *ui;
        SceneManager *sceneManager;

    public:
        NewMapWindow(QWidget *parent = 0, SceneManager *sceneManager = NULL);
        ~NewMapWindow();

    private:
        void connectEvents();
        void createMap();
        void previousScene();
};

#endif //EDITOR_NEWMAPWINDOW_H
