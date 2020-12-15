#include <iostream>
#include "Tile.h"

#define BITS 32

Tile::Tile(QWidget *parent, size_t xInBits, size_t yInBits)
    : coordinate(Coordinate(xInBits, yInBits)){
    QString texturePath = "../sprites/texture0.png";
    this->setPixmap(QPixmap(texturePath));
    this->setPos(this->coordinate.get_x() * BITS,
                 this->coordinate.get_y() * BITS);
    std::cout << "Coordenada x: " << this->coordinate.get_x() << '\n';
    std::cout << "Coordenada y: " << this->coordinate.get_y() << '\n';

}

Tile::~Tile() {

}

void Tile::changeImage() {
    this->setPixmap(QPixmap("../sprites/texture2.png"));
}

Coordinate Tile::getCoordinate() {
    return this->coordinate;
}