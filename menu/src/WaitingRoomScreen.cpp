#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include "WaitingRoomScreen.h"
#include "ui_WaitingRoomScreen.h"

WaitingRoomScreen::WaitingRoomScreen(QWidget *parent, ScreenManager *screenManager)
        : QWidget(parent), ui(new Ui::WaitingRoomScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;

    this->connectEvents();
}

WaitingRoomScreen::~WaitingRoomScreen() {
    delete this->ui;
}

void WaitingRoomScreen::connectEvents() {
    QPushButton *startButton = findChild<QPushButton*>("startButton");
    QObject::connect(startButton, &QPushButton::clicked, this, &WaitingRoomScreen::onStartButtonClick);

    QPushButton *refreshButton = findChild<QPushButton*>("refreshButton");
    QObject::connect(refreshButton, &QPushButton::clicked, this, &WaitingRoomScreen::onRefreshButtonClick);

    QPushButton *cancelButton = findChild<QPushButton*>("cancelButton");
    QObject::connect(cancelButton, &QPushButton::clicked, this, &WaitingRoomScreen::onCancelButtonClick);
}

void WaitingRoomScreen::onStartButtonClick() {

}

void WaitingRoomScreen::onRefreshButtonClick() {
    this->refresh();
}

void WaitingRoomScreen::onCancelButtonClick() {
    if (this->screenManager->tryToCancelMatch()) {
        this->screenManager->goBack();
        this->screenManager->goBack();
    }
}

void WaitingRoomScreen::refresh() {
    int level = this->screenManager->getLevel();
    int actualPlayers = this->screenManager->getActualPlayers();
    int maxPlayers = this->screenManager->getMaxPlayers();

    QLabel *levelLabel = findChild<QLabel*>("levelLabel");
    levelLabel->setText(QString::number(level));

    QLabel *actualLabel = findChild<QLabel*>("actualLabel");
    actualLabel->setText(QString::number(actualPlayers));

    QLabel *maxLabel = findChild<QLabel*>("maxLabel");
    maxLabel->setText(QString::number(maxPlayers));

}