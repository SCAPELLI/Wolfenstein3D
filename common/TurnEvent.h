#ifndef TURNEVENT_H
#define TURNEVENT_H

#include "AbstractEvent.h"
#include "../server/GameStage.h"
#include "client/CGame.h"
/*Evento de giro*/
enum TurningSense {ANTICLOCKWISE, CLOCKWISE};

class TurnEvent: public AbstractEvent {
public:
    int idPlayer;
    double degrees;
    TurnEvent(int idPlayer, double degrees): idPlayer(idPlayer), degrees(degrees) {}
    void runHandler(GameStage& gameStage) override;
    void runHandler(CGame& game);
    std::string getSerialization() override;
    double getDegrees();
};

#endif
