#include <QtWidgets/QPushButton>
#include <iostream>
#include <QtWidgets/QFileDialog>
#include <QDir>
#include "../include/EditorScene.h"
#include "ui_EditorScene.h"

EditorScene::EditorScene(QWidget *parent, ScreenManager *screenManager)
    : QMainWindow(parent), ui(new Ui::EditorScene) {

    this->ui->setupUi(this);
    this->screenManager = screenManager;
    QVBoxLayout *layout = findChild<QVBoxLayout*>("textureListLayout");
    this->textureList = new TextureList();
    layout->addWidget(this->textureList);

    this->tilemap = new Tilemap();
    QVBoxLayout *tilemapLayout = findChild<QVBoxLayout*>("tilemapLayout");
    tilemapLayout->addWidget(this->tilemap);

    connectEvents();
}

EditorScene::~EditorScene() {
    delete this->ui;
    delete this->textureList;
    delete this->tilemap;
}

void EditorScene::setMapSize(size_t rows, size_t columns) {
    this->tilemap->setMapSize(rows, columns);
}

void EditorScene::connectEvents() {
    QPushButton* button = findChild<QPushButton*>("saveButton");
    QObject::connect(button, &QPushButton::clicked, this, &EditorScene::saveMap);
}

void EditorScene::saveMap() {
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
}



/*

QString filter = "Yaml File (*.yaml)";
//QString file = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath(), filter);
QFileDialog qFileDialog;
QString filePath = qFileDialog.getSaveFileName(this,
                                        "Save file",
                                        QDir::homePath(),
                                        filter);
std::cout << filePath.toUtf8().constData();
QFile file(filePath);
if (!file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)) {
std::cout << "no se abrio";
}

if (this->mapFile.is_open()) {
    std::cout << "se guardo el archivo\n";
    // GUARDAR EL ARCHIVO
} else {
    QString filter = "Yaml File (*.yaml)";
    QString filePath = QFileDialog::getOpenFileName(this,
                                                "Open a file",
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
    }
}
*/
