#include "Tile.h"

#define BITS 32

Tile::Tile(QWidget *parent) {
    this->setPixmap(QPixmap("../sprites/texture0.png"));
}

Tile::~Tile() {

}

void Tile::changeImage() {
    this->setPixmap(QPixmap("../sprites/texture2.png"));
}
