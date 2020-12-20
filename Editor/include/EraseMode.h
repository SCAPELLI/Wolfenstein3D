#ifndef EDITOR_ERASEMODE_H
#define EDITOR_ERASEMODE_H

#include "Mode.h"

class EraseMode : public Mode {
    public:
        EraseMode(TilemapScene *tilemapScene);
        ~EraseMode();
        void executeClickResponse(Coordinate coordinate, QGraphicsItem *item) override;

};


#endif //EDITOR_ERASEMODE_H
