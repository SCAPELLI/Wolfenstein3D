#include <QtWidgets/QStyleOption>
#include "StartScreen.h"
#include "qpainter.h"
#include "ui_StartScreen.h"


StartScreen::StartScreen(QWidget *parent, ScreenManager *screenManager)
    : QWidget(parent), ui(new Ui::StartScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;
    this->setStyle();
}

StartScreen::~StartScreen() {
    delete this->ui;
}

void StartScreen::paintEvent(QPaintEvent *e) {
    /**
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
     **/
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap("../sprites/menu.png").scaled(size()));
    QWidget::paintEvent(e);
}

void StartScreen::setStyle() {
    //this->setStyleSheet("StartScreen {border-image: url(../sprites/menu.png); background-repeat: no-repeat}");

    /**
    QPixmap background("../sprites/menu.png");
    background = background.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
     **/
}