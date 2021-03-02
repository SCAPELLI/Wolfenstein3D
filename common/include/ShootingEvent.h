#ifndef SHOOTINGEVENT_H
#define SHOOTINGEVENT_H

#include "AbstractEvent.h"

class CGame;
/* Evento de disparo*/
class ShootingEvent: public AbstractEvent {
public:
    int idPlayer;
    //ShootingEvent(ShootingEvent& shootingEvent);
    ShootingEvent(int idPlayer);
    void runHandler(CGame& renderer) override;
    void runHandler(GameStage& game) override;
    std::string getSerialization() override;
};


#endif
