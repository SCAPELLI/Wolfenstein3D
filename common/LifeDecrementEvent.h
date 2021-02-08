#ifndef COLADEEVENTOS_LIFEDECREMENTEVENT_H
#define COLADEEVENTOS_LIFEDECREMENTEVENT_H

#include "AbstractEvent.h"

class CGame;

class LifeDecrementEvent: public AbstractEvent {
public:
    int idPlayer;
    LifeDecrementEvent(int idPlayer);
    std::string getSerialization() override;
    //LifeDecrementEvent(LifeDecrementEvent& lifeDecrementEvent);
    void runHandler(CGame& renderer) override;
};

#endif
