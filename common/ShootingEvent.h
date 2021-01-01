#ifndef SHOOTINGEVENT_H
#define SHOOTINGEVENT_H

#include "AbstractEvent.h"

class CGame;

class ShootingEvent: public AbstractEvent {
public:
    int idPlayer;
    ShootingEvent(ShootingEvent& shootingEvent);
    ShootingEvent(int idPlayer);
    void runHandler(CGame& renderer) override;
};


#endif
