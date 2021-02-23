#include "Texture.h"
#include <QtWidgets/QGraphicsPixmapItem>

Texture::Texture(const QString &texturePath, int id) {
    this->texturePath = texturePath;
    this->id = id;
}

Texture::~Texture() {}

QString Texture::getTexturePath() {
    return this->texturePath;
}

int Texture::getId() {
    return this->id;
}