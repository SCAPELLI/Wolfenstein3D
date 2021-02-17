#include <StartScreen.h>
#include <NicknameScreen.h>
#include <GamesScreen.h>
#include <NewMatchScreen.h>
#include <InfoScreen.h>
#include "ScreenManager.h"
#include "ui_ScreenManager.h"


ScreenManager::ScreenManager(QWidget *parent)
: QMainWindow(parent), ui(new Ui::ScreenManager) {
    this->ui->setupUi(this);
    this->screens = this->ui->screens;

    StartScreen *startScreen = new StartScreen(0, this);
    this->screens->addWidget(startScreen);

    InfoScreen *infoScreen = new InfoScreen(0, this);
    this->screens->addWidget(infoScreen);

    NicknameScreen *nicknameScreen = new NicknameScreen(0, this);
    this->screens->addWidget(nicknameScreen);

    GamesScreen *gamesScreen = new GamesScreen(0, this);
    this->screens->addWidget(gamesScreen);

    NewMatchScreen *newMatchScreen = new NewMatchScreen(0, this);
    this->screens->addWidget(newMatchScreen);

    this->screens->setCurrentIndex(0);


    /**
    QPixmap background("../sprites/menu.png");
    background = background.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
    this->screens->currentWidget()->setPalette(palette);
     **/
}

ScreenManager::~ScreenManager() noexcept {
    delete this->ui;
}

void ScreenManager::goNext() {
    if (this->screens->currentIndex() + 1 < this->screens->count()) {
        this->screens->setCurrentIndex(this->screens->currentIndex() + 1);
    }
}

void ScreenManager::goBack() {
    this->screens->setCurrentIndex(this->screens->currentIndex() - 1);
}