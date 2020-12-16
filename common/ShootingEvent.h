#ifndef SHOOTINGEVENT_H
#define SHOOTINGEVENT_H

#include "AbstractEvent.h"

class CGame;

class ShootingEvent: public AbstractEvent {
    int idPlayer;
public:
    ShootingEvent(ShootingEvent& shootingEvent);
    ShootingEvent(int idPlayer);
    void runHandler(CGame& renderer) override;
};


#endif
