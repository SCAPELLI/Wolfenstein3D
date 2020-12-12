#ifndef COLADEEVENTOS_LIFEDECREMENTEVENT_H
#define COLADEEVENTOS_LIFEDECREMENTEVENT_H

#include "AbstractEvent.h"

class Renderer;

class LifeDecrementEvent: public AbstractEvent {
public:
    void runHandler(Renderer& renderer) override;
};

#endif
