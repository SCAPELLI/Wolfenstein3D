#ifndef EDITOR_STYLE_H
#define EDITOR_STYLE_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>

class Style {
    public:
        void setRetroFont(QWidget *widget, size_t fontSize);
        void setButtonStyle(QPushButton *button, size_t fontSize);
        void setBrickBackgroundToScreen(QMainWindow* window);
        void setTabWidgetStyle(QTabWidget *tabWidget);
        void setListWidgetStyle(QListWidget* listWidget);
};


#endif //EDITOR_STYLE_H
