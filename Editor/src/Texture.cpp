#include "Texture.h"
#include <QtWidgets/QGraphicsPixmapItem>

Texture::Texture(const QString &texturePath) {
    this->texturePath = texturePath;
}

Texture::~Texture() {}

QString Texture::getTexturePath() {
    return this->texturePath;
}
