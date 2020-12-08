#include <fstream>
#include "../include/NewMapWindow.h"
#include "ui_NewMapWindow.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

#define MENU_SCREEN 0
#define EDITOR_SCREEN 2

#define PLAYER 1
#define WALL 2

const void createYaml(const std::string name, const std::string length, const std::string width);

NewMapWindow::NewMapWindow(QWidget *parent, ScreenManager *screenManager)
        : QMainWindow(parent), ui(new Ui::NewMapWindow) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;
    connectEvents();
}

NewMapWindow::~NewMapWindow() {
    delete this->ui;
}

void NewMapWindow::connectEvents() {
    QPushButton* acceptButton = findChild<QPushButton*>("acceptButton");
    QObject::connect(acceptButton, &QPushButton::clicked, this, &NewMapWindow::createMap);

    QPushButton* cancelButton = findChild<QPushButton*>("cancelButton");
    QObject::connect(cancelButton, &QPushButton::clicked, this, &NewMapWindow::previousScreen);
}

void NewMapWindow::createMap() {
    QLineEdit* name = findChild<QLineEdit*>("nameMap");
    QLineEdit* lenght = findChild<QLineEdit*>("lengthMap");
    QLineEdit* width = findChild<QLineEdit*>("widthMap");
    std::string nameText = name->text().toUtf8().constData();
    std::string lenghtText = lenght->text().toUtf8().constData();
    std::string widthText = width->text().toUtf8().constData();
    createYaml(nameText, lenghtText, widthText);
    this->nextScreen();
}

void NewMapWindow::previousScreen() {
    this->screenManager->changeScreen(MENU_SCREEN);
}

void NewMapWindow::nextScreen() {
    this->screenManager->changeScreen(EDITOR_SCREEN);
}

const void createYaml(const std::string name, const std::string length, const std::string width) {
    std::ofstream archive;
    std::string archiveName = "../maps/" + name + ".yaml";
    archive.open(archiveName, std::ios::out);
    YAML::Node map, _map = YAML::LoadFile(archiveName);
    _map["name"] = name;
    _map["length"] = length;
    _map["width"] = width;
    std::vector<std::vector<int>> matrix(std::stoi(length),
                                         std::vector<int> (std::stoi(width),0));
    int i, j;
    for (i = 0; i < matrix.size(); i++) {
        for (j = 0; j < matrix[i].size(); j++) {
            if (i == 0 || i == matrix.size() - 1 || j == 0 || j == matrix[i].size() - 1) {
                matrix[i][j] = WALL;
            }
        }
    }

    matrix[1][1] = PLAYER; // SACAR

    YAML::Node mapMatrix = _map["map"];
    for (i = 0; i < matrix.size(); i++) {
        YAML::Node row = YAML::Load("[]");
        for (j = 0; j < matrix[i].size(); j++) {
            row.push_back(matrix[i][j]);
        }
        _map["map"].push_back(row);
    }

    archive << _map;

}