#include <iostream>
#include <QtWidgets/QTableWidget>
#include <QHeaderView>
#include <QtWidgets/QListWidget>
#include "ScoreWindow.h"

#include "ui_ScoreWindow.h"
#include "common/include/Style.h"

#define FONT 25
#define HEADER_FONT 30
#define TITLE_WIDTH 516
#define TITLE_HEIGHT 120

#define BULLET_POS 0
#define KILL_POS 1
#define SCORE_POS 2

#define NAME_TABLE 0
#define KILL_TABLE 1
#define BULLET_TABLE 2
#define SCORE_TABLE 3

ScoreWindow::ScoreWindow(QWidget *parent, std::map<std::string, std::vector<int>> names)
    : QMainWindow(parent), ui(new Ui::ScoreWindow) {
    this->ui->setupUi(this);
    std::vector<std::pair<int, std::vector<std::string>>> highscores = this->sortMapByHighScore(names);
    this->setTable();
    this->setTableData(highscores);
    this->setStyle();
}

ScoreWindow::~ScoreWindow() {
    delete this->ui;
}

std::vector<std::pair<int, std::vector<std::string>>> ScoreWindow::sortMapByHighScore(
        std::map<std::string, std::vector<int>> names) {
    std::vector<std::pair<int, std::vector<std::string>>> highScores;
    for (auto &name:names) {
        std::string player = name.first;
        std::string bullets = std::to_string(name.second.at(BULLET_POS));
        std::string kills = std::to_string(name.second.at(KILL_POS));
        int score = name.second.at(SCORE_POS);
        std::pair<int, std::vector<std::string>> scoreByPlayer(score, {player, kills, bullets});
        highScores.push_back(scoreByPlayer);
    }
    std::sort(highScores.rbegin(), highScores.rend());
    return highScores;
}

void ScoreWindow::setTable() {
    QTableWidget *dataTable = findChild<QTableWidget*>("scoreTable");

    dataTable->setSelectionMode(QAbstractItemView::NoSelection);

    dataTable->setColumnCount(4);

    QStringList labels = {"name", "kills", "bullets fired", "score"};
    dataTable->setHorizontalHeaderLabels(labels);

    dataTable->verticalHeader()->hide();
    dataTable->horizontalHeader()->hide();
}

void ScoreWindow::setTableData(std::vector<std::pair<int, std::vector<std::string>>> scores) {
    for (auto &info:scores) {
        std::string score = std::to_string(info.first);
        std::string name = info.second.at(0);
        std::string kills = info.second.at(1);
        std::string bullets = info.second.at(2);
        this->addPlayer(name, kills, bullets, score);
    }
}

void ScoreWindow::addPlayer(std::string name, std::string kills, std::string bullets, std::string score) {
    QTableWidget *dataTable = findChild<QTableWidget*>("scoreTable");
    dataTable->insertRow(dataTable->rowCount());

    QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromUtf8(name.c_str()));
    nameItem->setTextAlignment(Qt::AlignCenter);
    dataTable->setItem(dataTable->rowCount() - 1, NAME_TABLE, nameItem);

    QTableWidgetItem *killsItem = new QTableWidgetItem(QString::fromUtf8(kills.c_str()));
    killsItem->setTextAlignment(Qt::AlignCenter);
    dataTable->setItem(dataTable->rowCount() - 1, KILL_TABLE, killsItem);

    QTableWidgetItem *bulletsItem = new QTableWidgetItem(QString::fromUtf8(bullets.c_str()));
    bulletsItem->setTextAlignment(Qt::AlignCenter);
    dataTable->setItem(dataTable->rowCount() - 1, BULLET_TABLE, bulletsItem);

    QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::fromUtf8(score.c_str()));
    scoreItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
    dataTable->setItem(dataTable->rowCount() - 1, SCORE_TABLE, scoreItem);
}

void ScoreWindow::setStyle() {
    QTableWidget *dataTable = findChild<QTableWidget*>("scoreTable");
    dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    Style style;
    style.setRetroFont(dataTable, FONT);
    style.setRetroFont(this->ui->nameLabel, HEADER_FONT);
    style.setRetroFont(this->ui->killsLabel, HEADER_FONT);
    style.setRetroFont(this->ui->bulletsLabel, HEADER_FONT);
    style.setRetroFont(this->ui->scoreLabel, HEADER_FONT);

    QString stylesheet = "QTableWidget {"
                         "  border: none"
                         "}";
    dataTable->setStyleSheet(stylesheet);

    QPixmap title("../sprites/highScores.png");
    this->ui->titleLabel->setPixmap(title.scaled(TITLE_WIDTH, TITLE_HEIGHT, Qt::KeepAspectRatio));
}