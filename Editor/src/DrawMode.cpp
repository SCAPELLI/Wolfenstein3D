#include "DrawMode.h"
#include "TilemapScene.h"

DrawMode::DrawMode(TilemapScene *tilemapScene) : Mode(tilemapScene) {}

DrawMode::~DrawMode() {}

void DrawMode::executeClickResponse(Coordinate &coordinate, QGraphicsItem *item) {
    this->tilemapScene->draw(coordinate, item);
}
