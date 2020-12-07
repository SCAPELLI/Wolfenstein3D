#ifndef MOVEMENTEVENT_H
#define MOVEMENTEVENT_H

#include "AbstractEvent.h"
#include "GameStage.h"

enum MovementDirection{FOWARD, BACKWARD};

class MovementEvent: public AbstractEvent {
    MovementDirection direction;

public:
    MovementEvent(MovementDirection direction): direction(direction){}
    void runHandler(GameStage& gameStage) override;
};

#endif
