#include "Mode.h"
#include "TilemapScene.h"

Mode::Mode(TilemapScene *tilemapScene)
    : tilemapScene(tilemapScene){}

Mode::~Mode() {}

void Mode::executeClickResponse(Coordinate &coordinate, QGraphicsItem *item) {}
