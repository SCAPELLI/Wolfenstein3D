#ifndef MOVEMENTEVENT_H
#define MOVEMENTEVENT_H

#include "AbstractEvent.h"
#include "../server/GameStage.h"

enum MovementDirection{BACKWARD, FORWARD};

class MovementEvent: public AbstractEvent {
public:
    MovementDirection direction;
    int idPlyr;

    MovementEvent(MovementDirection direction, int idPlyr)
    : direction(direction), idPlyr(idPlyr)  {}
    std::string getSerialization() override;
    void runHandler(GameStage& gameStage) override;
    MovementDirection getDirection();
};

#endif
