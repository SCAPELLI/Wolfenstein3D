#include <QtWidgets/QStyleOption>
#include "StartScreen.h"
#include "qpainter.h"
#include "ui_StartScreen.h"
#include "../../common/Style.h"


StartScreen::StartScreen(QWidget *parent, ScreenManager *screenManager)
    : QWidget(parent), ui(new Ui::StartScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;
    this->setStyle();
    connectEvents();
}

StartScreen::~StartScreen() {
    delete this->ui;
}

void StartScreen::connectEvents() {
    QPushButton *startButton = findChild<QPushButton*>("startButton");
    QObject::connect(startButton, &QPushButton::clicked, this, &StartScreen::clickJoinButton);
}

void StartScreen::clickJoinButton() {
    this->screenManager->goNext();
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
    QString sheetStyle =
            "QPushButton {"
                "background: none;"
                "border: none;"
                "margin: 0;"
                "padding: 0;"
                "color: rgb(170, 0, 0);"
                "font-weight: bold;"
                "outline: none"
            "}"
            "QPushButton:hover {"
            "color: rgb(220, 0, 0)"
            "}"
            "QPushButton:pressed {"
                "color: rgb(80, 0, 0)"
            "}";
    Style style;
    this->ui->startButton->setStyleSheet(sheetStyle);
    style.setRetroFont(this->ui->startButton, 25);
    //this->setStyleSheet("StartScreen {border-image: url(../sprites/menu.png); background-repeat: no-repeat}");

    /**
    QPixmap background("../sprites/menu.png");
    background = background.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
     **/
}