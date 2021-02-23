#include "Mode.h"
#include "Tilemap.h"

Mode::Mode(TilemapScene *tilemapScene)
    : tilemapScene(tilemapScene){}

Mode::~Mode() {}

void Mode::executeClickResponse(Coordinate &coordinate, QGraphicsItem *item) {}
