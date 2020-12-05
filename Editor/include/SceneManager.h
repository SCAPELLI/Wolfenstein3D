#ifndef EDITOR_SCENEMANAGER_H
#define EDITOR_SCENEMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets/QStackedWidget>

namespace Ui {
    class SceneManager;
}

class SceneManager : public QMainWindow {
    Q_OBJECT;

    private:
        Ui::SceneManager *ui;
        QStackedWidget *stack;

    public:
        SceneManager(QWidget *parent = 0);
        ~SceneManager();
        void changeScene(int scene);

};


#endif //EDITOR_SCENEMANAGER_H
