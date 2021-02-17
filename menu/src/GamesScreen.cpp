#include <QtWidgets/QTableWidget>
#include <QHeaderView>
#include <iostream>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QEventLoop>
#include <QtCore/QCoreApplication>
#include "GamesScreen.h"
#include "ui_GamesScreen.h"

#define MAPA 0
#define CANTIDAD_JUGADORES 1


GamesScreen::GamesScreen(QWidget *parent, ScreenManager *screenManager)
        : QWidget(parent), ui(new Ui::GamesScreen) {
    this->ui->setupUi(this);
    this->setDataTable();
    this->setStyle();

    QTableWidget *dataTable = findChild<QTableWidget*>("dataTable");

    MatchInfo match1(1, 666, 15, 8);
    this->addMatch(match1);
    MatchInfo match2(2, 420, 10, 2);
    this->addMatch(match2);
    
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

}

void GamesScreen::onJoinButtonClick() {
    QTableWidget *dataTable = findChild<QTableWidget*>("dataTable");
    if (dataTable->currentRow() >= 0) {
        std::cout << "Id del match seleccionado: " << this->idMatches.at(dataTable->currentRow()) << "\n";
    }
}

void GamesScreen::onRefreshButtonClick() {
    this->clearTable();

    //Aca llenamos la nueva info
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
    dataTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    dataTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}