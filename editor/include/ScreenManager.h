#ifndef EDITOR_SCREENMANAGER_H
#define EDITOR_SCREENMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets/QStackedWidget>

class MenuWindow;
class NewMapWindow;
class EditorScreen;

namespace Ui {
    class ScreenManager;
}

class ScreenManager : public QMainWindow {
    Q_OBJECT;

    private:
        Ui::ScreenManager *ui;
        QStackedWidget *stack;
        MenuWindow *menuWindow;
        EditorScreen *editorScene;

    public:
        ScreenManager(QWidget *parent = 0);
        ~ScreenManager();
        void changeScreen(int scene);

};

#endif //EDITOR_SCREENMANAGER_H
