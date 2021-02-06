#ifndef GAMEOVEREVENT_H
#define GAMEOVEREVENT_H
#include "Renderer.h"
#include "../AbstractEvent.h"

class GameOverEvent :  public AbstractEvent {
public:
    int idPlayer;
    GameOverEvent(GameOverEvent& gameOverEvent);
    GameOverEvent(int idPlayer);
    void runHandler(CGame& game) override;
};


#endif //GAME_H_GAMEOVEREVENT_H
