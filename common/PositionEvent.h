#ifndef GAME_H_POSITIONEVENT_H
#define GAME_H_POSITIONEVENT_H

#include "AbstractEvent.h"

class Renderer;

class PositionEvent : public AbstractEvent {
public:
    void runHandler(Renderer& renderer) override;
    PositionEvent(PositionEvent& updateEvent);
    PositionEvent(int x, int y);
};


#endif //GAME_H_POSITIONEVENT_H
