#ifndef COLADEEVENTOS_LIFEDECREMENTEVENT_H
#define COLADEEVENTOS_LIFEDECREMENTEVENT_H

#include "AbstractEvent.h"

class CGame;

class LifeDecrementEvent: public AbstractEvent {
    int idPlayer;
    int damage;
public:
    LifeDecrementEvent(int idPlayer, int damage);
    LifeDecrementEvent(LifeDecrementEvent& lifeDecrementEvent);
    void runHandler(CGame& renderer) override;
};

#endif
