#ifndef MOVEMENTEVENT_H
#define MOVEMENTEVENT_H

#include "AbstractEvent.h"
#include "GameStage.h"

enum MovementDirection{BACKWARD, FOWARD};

class MovementEvent: public AbstractEvent {
    MovementDirection direction;

public:
    explicit MovementEvent(MovementDirection direction): direction(direction) {}
    void runHandler(GameStage& gameStage) override;
    MovementDirection getDirection();
};

#endif
