#ifndef EDITOR_SCREENMANAGER_H
#define EDITOR_SCREENMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets/QStackedWidget>

namespace Ui {
    class ScreenManager;
}

class ScreenManager : public QMainWindow {
    Q_OBJECT;

    private:
        Ui::ScreenManager *ui;
        QStackedWidget *stack;

    public:
        ScreenManager(QWidget *parent = 0);
        ~ScreenManager();
        void changeScreen(int scene);
        void setMapFilePath();

};


#endif //EDITOR_SCREENMANAGER_H
