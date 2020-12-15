#include "Tile.h"

#define BITS 32

Tile::Tile(QWidget *parent, Coordinate coordinate, Texture texture)
    : coordinate(coordinate), texture(texture){
    QString texturePath = texture.getTexturePath();
    this->setPixmap(QPixmap(texturePath));
    this->setPos(this->coordinate.get_x() * BITS,
                 this->coordinate.get_y() * BITS);
}

Tile::~Tile() {

}

Coordinate Tile::getCoordinate() {
    return this->coordinate;
}
