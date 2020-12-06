#include "../include/TextureList.h"

#define ICON_SIZE 32

TextureList::TextureList(QWidget *parent)
    : QListWidget(parent) {

    setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    this->addTexture("../sprites/prueba.png");
    this->addTexture("../sprites/prueba1.png");
    this->addTexture("../sprites/prueba.png");
    this->addTexture("../sprites/prueba1.png");
    this->addTexture("../sprites/prueba.png");
    this->addTexture("../sprites/prueba1.png");
    this->addTexture("../sprites/logo.png");


    //this->addItem("hello");
}

TextureList::~TextureList() {

}

void TextureList::addTexture(std::string texturePath) {
    //QListWidgetItem *tile = new QListWidgetItem("holis");
    //QListWidgetItem *tile = new QListWidgetItem(QIcon("../sprites/prueba.png"), NULL);
    QString aux = QString::fromStdString(texturePath);
    QListWidgetItem *tile = new QListWidgetItem(QIcon(aux), aux);
    this->addItem(tile);
}