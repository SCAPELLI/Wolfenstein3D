#ifndef EDITOR_MODE_H
#define EDITOR_MODE_H

#include <QtWidgets/QGraphicsItem>
#include "Coordinate.h"

class TilemapScene;

class Mode {
    protected:
        TilemapScene *tilemapScene;

    public:
        Mode(TilemapScene *tilemapScene);
        ~Mode();
        virtual void executeClickResponse(Coordinate coordinate, QGraphicsItem *item);

};

#endif //EDITOR_MODE_H
