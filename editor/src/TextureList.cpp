#include "TextureList.h"
#include "SpriteTabs.h"
#include "../../common/Style.h"
#include <QMouseEvent>
#include <SpriteFileManager.h>

#define ICON_SIZE 32

TextureList::TextureList(QWidget *parent, SpriteTabs *spriteTabs) :
    spriteTabs(spriteTabs){
    this->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    this->setStyle();
}

TextureList::~TextureList() {
    int i;
    for (i = this->count() - 1; i >= 0; i--) {
        QListWidgetItem *item = this->takeItem(i);
        delete item;
    }
}

void TextureList::addTexture(const std::string &texturePath, const std::string &textureType, int id) {
    QString aux = QString::fromStdString(texturePath);
    QString auxType = QString::fromStdString(textureType);
    QListWidgetItem *tile = new QListWidgetItem(QIcon(aux), auxType);
    this->addItem(tile);

    Texture texture(aux, id);
    this->textures.push_back(texture);
}

void TextureList::mousePressEvent(QMouseEvent *event) {
    QListWidgetItem *item = itemAt(event->pos());
    this->setCurrentItem(item);
    QModelIndex aux = this->indexFromItem(item);
    int index = aux.row();
    this->spriteTabs->changeCurrentTexture(this->textures[index]);
}

void TextureList::setSpriteList(std::map<int, std::string> &spriteMap) {
    for (auto it = spriteMap.begin(); it != spriteMap.end(); it++) {
        std::string path = "../sprites/sprite" + std::to_string(it->first) + ".png";
        std::string type = it->second;
        this->addTexture(path, type, it->first);
    }
}

void TextureList::setStyle() {
    Style style;
    style.setListWidgetStyle(this);
}