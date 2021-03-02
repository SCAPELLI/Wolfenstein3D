#ifndef QUITEVENT_H
#define QUITEVENT_H

#include "AbstractEvent.h"
/*Evento que indica salir de la aplicación*/
class QuitEvent: public AbstractEvent {
public:
    int playerId;
    QuitEvent(int playerId);
    void runHandler(GameStage& gameStage) override;
    bool thisIsTheQuitEvent() override;
    std::string getSerialization() override;
};

#endif
