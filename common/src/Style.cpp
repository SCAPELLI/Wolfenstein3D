#include <QtGui/QFontDatabase>
#include <QtGui/QPainter>
#include <sstream>
#include "../include/Style.h"

void Style::setRetroFont(QWidget *widget, size_t fontSize) {
    int id = QFontDatabase::addApplicationFont("../../fonts/retro.ttf");
    QString retroFamily = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont retro(retroFamily);
    retro.setPointSize(fontSize);
    widget->setFont(retro);
}

void Style::setButtonStyle(QPushButton *button, size_t fontSize) {
    QString style = "QPushButton {"
                        "border-image:url(../../resources/button.png);"
                        "outline: none;"
                        "font-weight: bold;"
                        "width: 180px;"
                        "height: 20px;"
                        "color: rgb(167, 167, 167)"
                    "}";
    button->setStyleSheet(style);
    setRetroFont(button, fontSize);
}

void Style::setButtonStyle(QPushButton *button, size_t fontSize, size_t height, size_t width) {
    QString style1 = "QPushButton {"
                    "border-image:url(../../resources/button.png);"
                    "outline: none;"
                    "font-weight: bold;"
                    "color: rgb(167, 167, 167);";

    std::stringstream ss;
    ss << "height: " << std::to_string(height) << ";\n" << "width: " << std::to_string(width) << "}";
    std::string size = ss.str();
    char* sizeCharArray;
    sizeCharArray = &size[0];

    QString style2 = "QPushButton:hover {"
                     "color: rgb(200, 200, 200)"
                     "}"
                     "QPushButton:pressed {"
                     "color: rgb(140, 140, 140)"
                     "}";

    QString style;
    style.append(style1);
    style.append(sizeCharArray);
    style.append(style2);

    style.append(style);
    button->setStyleSheet(style);
    setRetroFont(button, fontSize);
}

void Style::setBrickBackgroundToScreen(QMainWindow *window) {
    QString style =
            "QMainWindow {"
                "background-image: url(../../Editor/sprites/sprite120.png)"
            "}";
    window->setStyleSheet(style);
}

void Style::setTabWidgetStyle(QTabWidget *tabWidget) {
    setRetroFont(tabWidget, 8);
    QString style =
                    "QTabBar::tab:selected {"
                        "background: rgb(88, 0, 0);"
                        "color: rgb(167, 167, 167)"
                    "}";
    tabWidget->setStyleSheet(style);
}

void Style::setListWidgetStyle(QListWidget *listWidget) {
    QString style =
            "QListWidget {"
                "background: rgb(88, 0, 0);"
            "}";
    listWidget->setStyleSheet(style);
    setRetroFont(listWidget, 10);
}