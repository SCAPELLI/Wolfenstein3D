#include "../include/EditorScene.h"
#include "ui_EditorScene.h"

EditorScene::EditorScene(QWidget *parent, SceneManager *sceneManager)
    : QMainWindow(parent), ui(new Ui::EditorScene) {
    this->ui->setupUi(this);
    this->sceneManager = sceneManager;
    QListWidget *textureList = findChild<QListWidget*>("textureList");
    this->textureList = new TextureList(textureList);
}

EditorScene::~EditorScene() {
    delete this->ui;

}