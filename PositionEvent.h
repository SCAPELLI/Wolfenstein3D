#ifndef GAME_H_POSITIONEVENT_H
#define GAME_H_POSITIONEVENT_H

#include "AbstractEvent.h"

class Renderer;

class PositionEvent : public AbstractEvent {
public:
    void runHandler(Renderer& renderer) override;
};


#endif //GAME_H_POSITIONEVENT_H
