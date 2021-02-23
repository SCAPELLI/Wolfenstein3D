#include "EraseMode.h"
#include "TilemapScene.h"

EraseMode::EraseMode(TilemapScene *tilemapScene) : Mode(tilemapScene) {}

EraseMode::~EraseMode() {}

void EraseMode::executeClickResponse(Coordinate &coordinate, QGraphicsItem *item) {
    this->tilemapScene->erase(coordinate, item);
}
