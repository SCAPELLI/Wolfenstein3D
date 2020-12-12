#ifndef COLADEEVENTOS_LIFEDECREMENTEVENT_H
#define COLADEEVENTOS_LIFEDECREMENTEVENT_H

#include "AbstractEvent.h"

class Renderer;

class LifeDecrementEvent: public AbstractEvent {
    int idPlayer;
    int damage;
public:
    LifeDecrementEvent(int idPlayer, int damage);
    LifeDecrementEvent(LifeDecrementEvent& lifeDecrementEvent);
    void runHandler(Renderer& renderer) override;
};

#endif
