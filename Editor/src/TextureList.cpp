#include "../include/TextureList.h"

#define ICON_SIZE 32

TextureList::TextureList(QListWidget *textureList) {
    this->textureList = textureList;
    this->textureList->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    this->addTexture("../sprites/prueba.png");
    this->addTexture("../sprites/prueba1.png");
    this->addTexture("../sprites/prueba.png");
    this->addTexture("../sprites/prueba1.png");
    this->addTexture("../sprites/prueba.png");
    this->addTexture("../sprites/prueba1.png");
    this->addTexture("../sprites/logo.png");
}

TextureList::~TextureList() {
    int i;
    for (i = 0; i < this->textureList->count(); i++) {
        QListWidgetItem *item = this->textureList->takeItem(i);
        delete item;
    }
}

void TextureList::addTexture(std::string texturePath) {
    QString aux = QString::fromStdString(texturePath);
    QListWidgetItem *tile = new QListWidgetItem(QIcon(aux), aux);
    this->textureList->addItem(tile);
}