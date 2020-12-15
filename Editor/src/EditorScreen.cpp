#include <QtWidgets/QPushButton>
#include <iostream>
#include <QtWidgets/QFileDialog>
#include <QDir>
#include <QtWidgets/QVBoxLayout>
#include "../include/EditorScreen.h"
#include "../include/TextureList.h"
#include "ui_EditorScreen.h"

EditorScreen::EditorScreen(QWidget *parent, ScreenManager *screenManager)
    : QMainWindow(parent), ui(new Ui::EditorScreen), currentTexture(Texture("../sprites/texture0.png")) {

    this->ui->setupUi(this);
    this->screenManager = screenManager;
    QVBoxLayout *layout = findChild<QVBoxLayout*>("textureListLayout");
    this->textureList = new TextureList(0, this);
    layout->addWidget(this->textureList);

    this->tilemap = new Tilemap();
    QVBoxLayout *tilemapLayout = findChild<QVBoxLayout*>("tilemapLayout");
    tilemapLayout->addWidget(this->tilemap);

    connectEvents();
}

EditorScreen::~EditorScreen() {
    delete this->ui;
    delete this->textureList;
    delete this->tilemap;
}

void EditorScreen::setMapSize(size_t rows, size_t columns) {
    this->tilemap->setMapSize(rows, columns);
}

void EditorScreen::connectEvents() {
    QPushButton* button = findChild<QPushButton*>("saveButton");
    QObject::connect(button, &QPushButton::clicked, this, &EditorScreen::saveMap);
}

void EditorScreen::saveMap() {
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

void EditorScreen::changeCurrentTexture(Texture newTexture) {
    this->currentTexture = newTexture;
}