#include <QtWidgets/QTableWidget>
#include <QHeaderView>
#include <iostream>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QEventLoop>
#include <QtCore/QCoreApplication>
#include <QtGui/QPainter>
#include <QtWidgets/QMessageBox>
#include <unistd.h>
#include "client/include/GamesScreen.h"
#include "client/ui/ui_GamesScreen.h"
#include "../../common/Style.h"

#define MAPA 0
#define CANTIDAD_JUGADORES 1

#define HEADER_FONT 15
#define INFO_FONT 8
#define BUTTON_FONT 15
#define BUTTON_HEIGHT 30
#define BUTTON_WIDTH 120


GamesScreen::GamesScreen(QWidget *parent, ScreenManager *screenManager)
        : QWidget(parent), ui(new Ui::GamesScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;

    this->setDataTable();
    this->setStyle();
    this->connectEvents();
}

GamesScreen::~GamesScreen() {
    delete this->ui;
}

void GamesScreen::connectEvents() {
    QPushButton *joinButton = findChild<QPushButton*>("joinButton");
    QObject::connect(joinButton, &QPushButton::clicked, this, &GamesScreen::onJoinButtonClick);

    QPushButton *refreshButton = findChild<QPushButton*>("refreshButton");
    QObject::connect(refreshButton, &QPushButton::clicked, this, &GamesScreen::onRefreshButtonClick);

    QPushButton *createButton = findChild<QPushButton*>("createButton");
    QObject::connect(createButton, &QPushButton::clicked, this, &GamesScreen::onCreateButtonClick);
}

void GamesScreen::onJoinButtonClick() {
    QTableWidget *dataTable = findChild<QTableWidget*>("dataTable");
    //QMessageBox waitingMessage;
    /*waitingMessage.setText("Waiting for the match to start...");
    waitingMessage.setStandardButtons(0);
    waitingMessage.setWindowFlag(Qt::WindowCloseButtonHint, false);
    waitingMessage.setWindowFlags(Qt::WindowTitleHint);
    waitingMessage.exec();*/
    if (dataTable->currentRow() >= 0) {
        if (!(this->screenManager->tryToJoin(this->idMatches.at(dataTable->currentRow())))) {
            QMessageBox waitingMessage;
            waitingMessage.setText("An error has occurred");
            waitingMessage.exec();
            refresh();
        }
    }
}

void GamesScreen::onRefreshButtonClick() {
    this->refresh();
}

void GamesScreen::onCreateButtonClick() {
    this->screenManager->goNext();
}

void GamesScreen::refresh() {
    this->clearTable();

    std::vector<MatchInfo> matches = this->screenManager->requestMatches();

    for (auto &match: matches) {
        this->addMatch(match);
    }
}

void GamesScreen::addMatch(MatchInfo match) {
    this->idMatches.push_back(match.getMatchId());

    QTableWidget *dataTable = findChild<QTableWidget*>("dataTable");
    dataTable->insertRow(dataTable->rowCount());
    dataTable->setItem(dataTable->rowCount() - 1, MAPA, new QTableWidgetItem(QString::number(match.getLevelId())));
    QString numberOfPlayers;
    numberOfPlayers.append(QString::number(match.getActualNumberOfUsers()));
    numberOfPlayers.append(" / ");
    numberOfPlayers.append(QString::number((match.getMaximumNumberOfUsers())));
    dataTable->setItem(dataTable->rowCount() - 1, CANTIDAD_JUGADORES, new QTableWidgetItem(numberOfPlayers));
}

void GamesScreen::clearTable() {
    QTableWidget *dataTable = findChild<QTableWidget*>("dataTable");
    dataTable->setRowCount(0);
    this->idMatches.clear();
}

void GamesScreen::setDataTable() {
    QTableWidget *dataTable = findChild<QTableWidget*>("dataTable");

    dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    dataTable->setSelectionMode(QAbstractItemView::SingleSelection);

    dataTable->setColumnCount(2);

    QStringList labels = {"Mapa", "Cantidad de jugadores"};
    dataTable->setHorizontalHeaderLabels(labels);
}

void GamesScreen::setStyle() {
    QTableWidget *dataTable = findChild<QTableWidget*>("dataTable");
    dataTable->horizontalHeader()->setSectionResizeMode(0,
                                                        QHeaderView::Stretch);
    dataTable->horizontalHeader()->setSectionResizeMode(1,
                                                        QHeaderView::ResizeToContents);

    Style style;
    style.setRetroFont(dataTable, INFO_FONT);
    style.setRetroFont(dataTable->horizontalHeader(), HEADER_FONT);

    QString stylesheet = "QTableWidget {"
                         "  background: rgb(80, 0, 0);"
                         "  gridline-color: red;"
                         "  color: red;"
                         "}"
                         "QHeaderView::section {"
                         "  color: rgb(80, 0, 0);"
                         "}";

    dataTable->setStyleSheet(stylesheet);

    style.setButtonStyle(this->ui->joinButton,
                         BUTTON_FONT, BUTTON_HEIGHT,
                         BUTTON_WIDTH);
    style.setButtonStyle(this->ui->refreshButton,
                         BUTTON_FONT, BUTTON_HEIGHT,
                         BUTTON_WIDTH);
    style.setButtonStyle(this->ui->createButton,
                         BUTTON_FONT, BUTTON_HEIGHT,
                         BUTTON_WIDTH);
}

