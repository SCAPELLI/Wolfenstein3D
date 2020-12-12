#ifndef GAMEOVEREVENT_H
#define GAMEOVEREVENT_H
#include "Renderer.h"
#include "AbstractEvent.h"

class GameOverEvent :  public AbstractEvent {
public:
    GameOverEvent();
    void runHandler(Renderer& renderer) override;
};


#endif //GAME_H_GAMEOVEREVENT_H
