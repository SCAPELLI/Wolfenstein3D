#include "TextureList.h"
#include "SpriteTabs.h"
#include <QMouseEvent>
#include <SpriteFileManager.h>

#define ICON_SIZE 32

TextureList::TextureList(QWidget *parent, SpriteTabs *spriteTabs) :
    spriteTabs(spriteTabs){
    this->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
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
    this->spriteTabs->changeCurrentTexture(this->textures[index]);
}

void TextureList::setSpriteList(std::map<int, std::string> spriteMap) {
    for (auto it = spriteMap.begin(); it != spriteMap.end(); it++) {
        std::string path = "../sprites/sprite" + std::to_string(it->first) + ".png";
        this->addTexture(path);
    }
}