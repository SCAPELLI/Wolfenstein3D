#include "TextureList.h"
#include "EditorScreen.h"
#include <QMouseEvent>

#define ICON_SIZE 32

TextureList::TextureList(QWidget *parent, EditorScreen *editorScreen) :
    editorScreen(editorScreen){
    this->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    this->addTexture("../sprites/texture0.png");
    this->addTexture("../sprites/texture1.png");
    this->addTexture("../sprites/texture2.png");
    this->addTexture("../sprites/texture3.png");
    this->addTexture("../sprites/texture4.png");
    this->addTexture("../sprites/texture5.png");
    this->addTexture("../sprites/texture6.png");
    this->addTexture("../sprites/sprite221.png");
    this->addTexture("../sprites/sprite000.png");
}

TextureList::~TextureList() {
    int i;
    for (i = this->count() - 1; i >= 0; i--) {
        QListWidgetItem *item = this->takeItem(i);
        delete item;
    }
}

void TextureList::addTexture(std::string texturePath) {
    QString aux = QString::fromStdString(texturePath);
    QListWidgetItem *tile = new QListWidgetItem(QIcon(aux), aux);
    this->addItem(tile);

    Texture texture(aux);
    this->textures.push_back(texture);
}

void TextureList::mousePressEvent(QMouseEvent *event) {
    QListWidgetItem *item = itemAt(event->pos());
    this->setCurrentItem(item);
    QModelIndex aux = this->indexFromItem(item);
    int index = aux.row();
    this->editorScreen->changeCurrentTexture(this->textures[index]);
}