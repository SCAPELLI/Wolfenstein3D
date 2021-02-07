#include <QtWidgets/QLabel>
#include <QtGui/QFontDatabase>
#include "../include/MenuScreen.h"
#include "ui_MenuScreen.h"

MenuScreen::MenuScreen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MenuScreen){
    this->ui->setupUi(this);
    this->actualBackgroundNameFile = "../sprites/menu.png";
    this->setBackground();
    this->setButtonStyle();
}

MenuScreen::~MenuScreen() {
    delete this->ui;
}

void MenuScreen::setBackground() {
    QPixmap background(this->actualBackgroundNameFile);
    background = background.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
}

void MenuScreen::setButtonStyle() {
    int id = QFontDatabase::addApplicationFont("../fonts/retro.ttf");
    QString retroFamily = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont retro(retroFamily);
    retro.setPointSize(25);
    this->ui->startButton->setFont(retro);
}

void MenuScreen::resizeEvent(QResizeEvent *event) {
    this->setBackground();
}