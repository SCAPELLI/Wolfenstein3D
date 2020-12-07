#include <iostream>
#include "../include/TextureList.h"

#define ICON_SIZE 32

TextureList::TextureList(QWidget *parent) {
    //this->textureList = textureList;
    //this->textureList->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    this->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
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
    for (i = this->count() - 1; i >= 0; i--) {
        QListWidgetItem *item = this->takeItem(i);
        delete item;
    }
}

void TextureList::addTexture(std::string texturePath) {
    QString aux = QString::fromStdString(texturePath);
    QListWidgetItem *tile = new QListWidgetItem(QIcon(aux), aux);
    this->addItem(tile);
}

void TextureList::dragEnterEvent(QDragEnterEvent *event) {

}

void TextureList::mousePressEvent(QMouseEvent *event) {
    std::cout << "presionado!\n";
}