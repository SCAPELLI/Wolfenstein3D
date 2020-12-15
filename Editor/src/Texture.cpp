#include <QtWidgets/QGraphicsPixmapItem>
#include "Texture.h"

Texture::Texture(const QString &texturePath) {
    this->texturePath = texturePath;
}

Texture::~Texture() {

}

QString Texture::getTexturePath() {
    return this->texturePath;
}

void Texture::setTexturePath(const QString &texturePath) {
    this->texturePath = texturePath;
}