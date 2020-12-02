#include <fstream>
#include "../include/NewMapWindow.h"
#include "ui_NewMapWindow.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

#define PLAYER 1
#define WALL 2

const void createYaml(const std::string name, const std::string length, const std::string width);

NewMapWindow::NewMapWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::NewMapWindow) {
    this->ui->setupUi(this);
    connectEvents();
}

NewMapWindow::~NewMapWindow() {
    delete this->ui;
}

void NewMapWindow::connectEvents() {
    QPushButton* acceptButton = findChild<QPushButton*>("acceptButton");
    QObject::connect(acceptButton, &QPushButton::clicked, this, &NewMapWindow::createMap);
}

void NewMapWindow::createMap() {
    QLineEdit* name = findChild<QLineEdit*>("nameMap");
    QLineEdit* lenght = findChild<QLineEdit*>("lengthMap");
    QLineEdit* width = findChild<QLineEdit*>("widthMap");
    std::string nameText = name->text().toUtf8().constData();
    std::string lenghtText = lenght->text().toUtf8().constData();
    std::string widthText = width->text().toUtf8().constData();
    createYaml(nameText, lenghtText, widthText);

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
            if (i == 0 || i == matrix.size() - 1 || j == 0 || j == matrix[i].size()) {
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

    YAML::Node info = _map["info"];
    YAML::Node player = info["player"];
    player["id"] = PLAYER;
    player["sprite"] = "ruta de sprite";
    YAML::Node wall = info["wall"];
    wall["id"] = WALL;
    wall["sprite"] = "ruta de sprite";

    archive << _map;
}