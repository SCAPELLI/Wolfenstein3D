#include <QtWidgets/QLabel>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QLineEdit>
#include "../include/MenuScreen.h"
#include "client/ui/ui_MenuScreen.h"

#define MENU_SCREEN 0
#define NICKNAME_SCREEN 1
#define SERVERS_SCREEN 2

MenuScreen::MenuScreen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MenuScreen){
    this->ui->setupUi(this);
    this->actualBackgroundNameFile = "../sprites/menu.png";
    this->setMenuBackground();
    this->setButtonStyle();
    this->connectEvents();
}

MenuScreen::~MenuScreen() {
    delete this->ui;
}

void MenuScreen::connectEvents() {
    QPushButton* startButton = findChild<QPushButton*>("startButton");
    QObject::connect(startButton, &QPushButton::clicked, this, &MenuScreen::changeToNicknameScreen);

    QPushButton* acceptButton = findChild<QPushButton*>("acceptButton");
    QObject::connect(acceptButton, &QPushButton::clicked, this, &MenuScreen::acceptButtonEvent);

    QPushButton* cancelButton = findChild<QPushButton*>("cancelButton");
    QObject::connect(cancelButton, &QPushButton::clicked, this, &MenuScreen::cancelButtonEvent);
}

void MenuScreen::setMenuBackground() {
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
    this->ui->acceptButton->setFont(retro);
    this->ui->cancelButton->setFont(retro);
    this->ui->nicknameLine->setFont(retro);
    retro.setPointSize(40);
    this->ui->nicknameLabel->setFont(retro);
}

void MenuScreen::resizeEvent(QResizeEvent *event) {
    if (this->ui->stackedWidget->currentIndex() == MENU_SCREEN) {
            this->setMenuBackground();
    } else {
        setNicknameBackground();
    }
}

void MenuScreen::setNicknameBackground() {
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::darkRed);
    this->setPalette(palette);
}

void MenuScreen::changeToNicknameScreen() {
    this->ui->stackedWidget->setCurrentIndex(NICKNAME_SCREEN);
    this->setNicknameBackground();
}

void MenuScreen::changeToMenuScreen() {
    this->ui->stackedWidget->setCurrentIndex(MENU_SCREEN);
    this->setMenuBackground();
}

void MenuScreen::acceptButtonEvent() {
    QLineEdit *line = findChild<QLineEdit*>("nicknameLine");
    if (!line->text().isEmpty()) {
        this->ui->stackedWidget->setCurrentIndex(SERVERS_SCREEN);
    }
}

void MenuScreen::cancelButtonEvent() {
    this->ui->nicknameLine->clear();
}