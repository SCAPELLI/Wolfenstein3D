#include "Tilemap.h"

#include <QtWidgets/QLabel>

#define BITS 32

Tilemap::Tilemap(QWidget *parent, EditorScreen *editorScreen)
    : editorScreen(editorScreen) {
    this->scene = new TilemapScene(editorScreen);
    this->setScene(this->scene);
    this->show();
}

Tilemap::~Tilemap() {
    delete this->scene;
}

void Tilemap::setMapSize(size_t rows, size_t columns) {
    //this->resize(this->rows * BITS, this->columns * BITS);
    this->scene->setMapSize(rows, columns);
}

void Tilemap::changeToDrawMode() {
    this->scene->changeToDrawMode();
}

void Tilemap::changeToEraseMode() {
    this->scene->changeToEraseMode();
}
