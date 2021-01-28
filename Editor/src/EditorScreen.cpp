#include <QtWidgets/QPushButton>
#include <iostream>
#include <QtWidgets/QFileDialog>
#include <QDir>
#include <QtWidgets/QVBoxLayout>
#include <NewMapDialog.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include "../include/EditorScreen.h"
#include "../include/TilemapScene.h"
#include "ui_EditorScreen.h"

EditorScreen::EditorScreen(QWidget *parent, ScreenManager *screenManager)
    : QMainWindow(parent), ui(new Ui::EditorScreen), currentTexture(Texture("../sprites/sprite100.png", "wall", 100)) {

    this->ui->setupUi(this);
    this->screenManager = screenManager;

    QGraphicsView* tilemap = findChild<QGraphicsView*>("tilemap");
    this->tilemapScene = new TilemapScene(this);
    tilemap->setScene(this->tilemapScene);
    tilemap->show();
    QVBoxLayout *tilemapLayout = findChild<QVBoxLayout*>("tilemapLayout");
    tilemapLayout->addWidget(tilemap);

    QVBoxLayout *spriteTabLayout = findChild<QVBoxLayout*>("textureListLayout");
    this->spriteTabs = new SpriteTabs(0, this);
    spriteTabLayout->addWidget(this->spriteTabs);

    connectEvents();
}

EditorScreen::~EditorScreen() {
    delete this->ui;
    delete this->tilemapScene;
    delete this->spriteTabs;
}

void EditorScreen::connectEvents() {
    QPushButton* newButton = findChild<QPushButton*>("newButton");
    QObject::connect(newButton, &QPushButton::clicked, this, &EditorScreen::newMap);

    QPushButton* button = findChild<QPushButton*>("saveButton");
    QObject::connect(button, &QPushButton::clicked, this, &EditorScreen::saveMap);

    QPushButton* drawButton = findChild<QPushButton*>("drawButton");
    QObject::connect(drawButton, &QPushButton::clicked, this, &EditorScreen::changeToDrawMode);

    QPushButton* eraseButton = findChild<QPushButton*>("eraseButton");
    QObject::connect(eraseButton, &QPushButton::clicked, this, &EditorScreen::changeToEraseMode);
}

void EditorScreen::newMap() {
    NewMapDialog newMapDialog;
    newMapDialog.exec();

    int lenght;
    int width;

    if (newMapDialog.giveLenghtWidthIfHasAValidState(&lenght, &width)) {
        delete this->tilemapScene;
        this->tilemapScene = new TilemapScene(this);
        QGraphicsView* tilemap = findChild<QGraphicsView*>("tilemap");
        tilemap->setScene(this->tilemapScene);
        tilemap->show();
        this->tilemapScene->setMapSize(lenght, width);
    }
}

void EditorScreen::saveMap() {
    if (!this->fileName.empty()) {
        this->createMapYalm();
    } else {
        QString filter = "Yaml File (*.yaml)";
        QString filePath = QFileDialog::getSaveFileName(this,
                                                        "Save the file",
                                                        QDir::homePath(),
                                                        filter);
        std::string aux = filePath.toUtf8().toStdString();
        if (aux.empty()) {
            //LEVANTAR UNA VENTANA QUE INFORME QUE NO SE PUDO GUARDAR
            // DEBERIA HACER UNA FUNCION QUE DEVUELVA TRUE SI SE PUDO GUARDAR
            std::cout << "no puso file path uwu\n";
        } else {
            this->fileName = aux + ".yaml";
            std::cout << "Filename: " << this->fileName << "\n";
            this->createMapYalm();
        }
    }


    /**
    //Si ya existe, guardo ahi
    if (this->mapFile.is_open()) {
        std::cout << "se guardo el archivo\n";
        // GUARDAR EL ARCHIVO
        // LEVANTAR UNA VENTANA QUE INFORME QUE SE GUARDO
    } else {
        QString filter = "Yaml File (*.yaml)";
        QString filePath = QFileDialog::getSaveFileName(this,
                                                        "Save the file",
                                                        QDir::homePath(),
                                                        filter);
        std::string aux = filePath.toUtf8().toStdString() + ".yaml";
        std::cout << aux << '\n';
        this->mapFile.open(aux, std::ios::out);
        if (!this->mapFile.is_open()) {
            std::cout << "no se pudo abrir el archivo\n";
            // LEVANTAR UNA VENTANITA QUE LO INFORME
        } else {
            // GUARDAR EL ARCHIVO
            // LRVANTAR UNA VENTANA QUE LO INFORME
        }
    }
     **/

}

void EditorScreen::changeCurrentTexture(Texture newTexture) {
    this->currentTexture = newTexture;
}

Texture EditorScreen::getCurrentTexture() {
    return this->currentTexture;
}

void EditorScreen::changeToDrawMode() {
    this->tilemapScene->changeToDrawMode();
}

void EditorScreen::changeToEraseMode() {
    this->tilemapScene->changeToEraseMode();
}

void EditorScreen::createMapYalm() {
    std::ofstream file;
    file.open(this->fileName, std::ios::out);
    YAML::Node map, _map = YAML::LoadFile(this->fileName);
    YAML::Node mapMatrix = _map["map"];
    std::vector<std::vector<int>> matrix = this->tilemapScene->getMapMatrix();

    int i;
    int j;

    for (i = 0; i < matrix.size(); i++) {
        YAML::Node row = YAML::Load("[]");
        for (j = 0; j < matrix[i].size(); j++) {
            row.push_back(matrix[i][j]);
        }
        _map["map"].push_back(row);
    }

    file << _map;
}