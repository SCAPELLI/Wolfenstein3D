#include "../include/EditorScene.h"
#include "ui_EditorScene.h"

EditorScene::EditorScene(QWidget *parent, SceneManager *sceneManager)
    : QMainWindow(parent), ui(new Ui::EditorScene) {
    this->ui->setupUi(this);
    this->sceneManager = sceneManager;
    //QListWidget *textureList = findChild<QListWidget*>("textureList");
    QVBoxLayout *layout = findChild<QVBoxLayout*>("textureListLayout");
    layout->addWidget(new TextureList());

}

EditorScene::~EditorScene() {
    delete this->ui;
    delete this->textureList;

}