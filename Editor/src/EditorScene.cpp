#include "../include/EditorScene.h"
#include "ui_EditorScene.h"

EditorScene::EditorScene(QWidget *parent, SceneManager *sceneManager)
    : QMainWindow(parent), ui(new Ui::EditorScene) {

    this->ui->setupUi(this);
    this->sceneManager = sceneManager;
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