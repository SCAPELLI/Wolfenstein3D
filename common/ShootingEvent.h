#ifndef SHOOTINGEVENT_H
#define SHOOTINGEVENT_H

#include "AbstractEvent.h"

class Renderer;

class ShootingEvent: public AbstractEvent {
public:
    void runHandler(Renderer& renderer) override;
};


#endif
