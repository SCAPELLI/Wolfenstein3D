#include <QtWidgets/QTableWidget>
#include <QHeaderView>
#include <iostream>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include "GamesScreen.h"
#include "ui_GamesScreen.h"


GamesScreen::GamesScreen(QWidget *parent, ScreenManager *screenManager)
        : QWidget(parent), ui(new Ui::GamesScreen) {
    this->ui->setupUi(this);
    this->setDataTable();
    this->setStyle();

    QTableWidget *dataTable = findChild<QTableWidget*>("dataTable");

    dataTable->insertRow(0);
    dataTable->setItem(0, 0, new QTableWidgetItem("Mapa 1"));
    dataTable->setItem(0, 1, new QTableWidgetItem("5/6"));
    dataTable->insertRow(1);
    dataTable->setItem(1, 0, new QTableWidgetItem("Mapa 2"));
    dataTable->setItem(1, 1, new QTableWidgetItem("2/10"));

    this->connectEvents();
}

GamesScreen::~GamesScreen() {
    delete this->ui;
}

void GamesScreen::connectEvents() {
    QPushButton *joinButton = findChild<QPushButton*>("joinButton");
    QObject::connect(joinButton, &QPushButton::clicked, this, &GamesScreen::onJoinButtonClick);
}

void GamesScreen::onJoinButtonClick() {
    QTableWidget *dataTable = findChild<QTableWidget*>("dataTable");
    QList<QTableWidgetItem*> list = dataTable->selectedItems();
    std::cout << "Seleccionado: " << dataTable->currentRow() << "\n";
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