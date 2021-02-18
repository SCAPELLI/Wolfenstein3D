#include <StartScreen.h>
#include <NicknameScreen.h>
#include <GamesScreen.h>
#include <NewMatchScreen.h>
#include <InfoScreen.h>
#include <WaitingRoomScreen.h>
#include "ScreenManager.h"
#include "ui_ScreenManager.h"


ScreenManager::ScreenManager(QWidget *parent, Client *client)
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

    this->waitingRoomScreen = new WaitingRoomScreen(0, this);
    this->screens->addWidget(this->waitingRoomScreen);

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

ScreenManager::~ScreenManager() {
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

bool ScreenManager::tryToConnect(std::string port, std::string domain) {
    return this->client->tryToConnect(port, domain);
}

bool ScreenManager::tryToSubmitUsername(std::string nickname) {
    return this->client->tryToSubmitUsername(nickname);
}

bool ScreenManager::tryToJoin(int matchId) {
    return this->client->tryToJoin(matchId);
}

std::vector<MatchInfo> ScreenManager::requestMatches() {
    return this->client->requestMatches();
}

bool ScreenManager::tryToCreateAMatch(int level, int maxPlayer) {
    return this->client->tryToCreateAMatch(level, maxPlayer);
}

int ScreenManager::getLevel() {
    return this->client->getLevel();
}

int ScreenManager::getActualPlayers() {
    return this->client->getActualPlayers();
}

int ScreenManager::getMaxPlayers() {
    return this->client->getMaxPlayers();
}

void ScreenManager::refreshWaitingRoom() {
    this->waitingRoomScreen->refresh();
}

bool ScreenManager::tryToCancelMatch() {
    return this->client->tryToCancelMatch();
}