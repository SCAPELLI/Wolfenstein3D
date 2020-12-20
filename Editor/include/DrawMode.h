#ifndef EDITOR_DRAWMODE_H
#define EDITOR_DRAWMODE_H

#include <Mode.h>

class DrawMode : public Mode {
    public:
        DrawMode(TilemapScene *tilemapScene);
        ~DrawMode();
        void executeClickResponse(Coordinate coordinate, QGraphicsItem *item) override;

};


#endif //EDITOR_DRAWMODE_H
