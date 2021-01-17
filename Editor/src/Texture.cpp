#include "Texture.h"
#include <QtWidgets/QGraphicsPixmapItem>

Texture::Texture(const QString &texturePath, const QString &textureType, int id) {
    this->texturePath = texturePath;
    this->type = textureType;
    this->id = id;
}

Texture::~Texture() {}

QString Texture::getTexturePath() {
    return this->texturePath;
}

QString Texture::getTextureType() {
    return this->type;
}