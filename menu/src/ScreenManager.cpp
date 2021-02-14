#include <StartScreen.h>
#include "ScreenManager.h"
#include "ui_ScreenManager.h"


ScreenManager::ScreenManager(QWidget *parent)
: QMainWindow(parent), ui(new Ui::ScreenManager) {
    this->ui->setupUi(this);
    this->screens = this->ui->screens;
    StartScreen *startScreen = new StartScreen(0, this);
    this->screens->addWidget(startScreen);
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
