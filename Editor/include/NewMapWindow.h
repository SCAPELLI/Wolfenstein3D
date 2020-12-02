#ifndef EDITOR_NEWMAPWINDOW_H
#define EDITOR_NEWMAPWINDOW_H

#include <QMainWindow>
#include <QWidget>

namespace Ui {
    class NewMapWindow;
}

class NewMapWindow : public QMainWindow {
    Q_OBJECT

    private:
        Ui::NewMapWindow *ui;

    public:
        NewMapWindow(QWidget *parent = 0);
        ~NewMapWindow();

    private:
        void connectEvents();
        void createMap();
};

#endif //EDITOR_NEWMAPWINDOW_H
