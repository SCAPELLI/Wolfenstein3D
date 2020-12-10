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
}

EditorScene::~EditorScene() {
    delete this->ui;
    delete this->textureList;
}

void EditorScene::setMapSize(size_t rows, size_t columns) {
    this->tilemap->setMapSize(rows, columns);
}
