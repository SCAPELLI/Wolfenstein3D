#include "NewMatchScreen.h"
#include "ui_NewMatchScreen.h"

NewMatchScreen::NewMatchScreen(QWidget *parent, ScreenManager *screenManager)
    : QWidget(parent), ui(new Ui::NewMatchScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;
}

NewMatchScreen::~NewMatchScreen() {
    delete this->ui;
}
