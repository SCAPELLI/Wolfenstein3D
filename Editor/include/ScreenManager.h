#ifndef EDITOR_SCREENMANAGER_H
#define EDITOR_SCREENMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets/QStackedWidget>

class MenuWindow;
class NewMapWindow;
class EditorScene;

namespace Ui {
    class ScreenManager;
}

class ScreenManager : public QMainWindow {
    Q_OBJECT;

    private:
        Ui::ScreenManager *ui;
        QStackedWidget *stack;
        MenuWindow *menuWindow;
        NewMapWindow *newMapWindow;
        EditorScene *editorScene;

    public:
        ScreenManager(QWidget *parent = 0);
        ~ScreenManager();
        void changeScreen(int scene);
        void setMapFilePath(const std::string &path);

};


#endif //EDITOR_SCREENMANAGER_H
