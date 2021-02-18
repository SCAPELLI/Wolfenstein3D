#ifndef GAMEOVEREVENT_H
#define GAMEOVEREVENT_H
#include "../AbstractEvent.h"
#include "Event.h"


class GameOverEvent :  public AbstractEvent {
public:
    int idPlayer;
    updateEventType eventType;
    GameOverEvent (GameOverEvent& gameOverEvent);
    GameOverEvent (updateEventType eventType, int idPlayer);
    void runHandler(CGame& game) override;
    updateEventType getEventType();
    std::string getSerialization() override;
};


#endif //GAME_H_GAMEOVEREVENT_H
