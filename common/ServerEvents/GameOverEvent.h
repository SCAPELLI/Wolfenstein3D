#ifndef GAMEOVEREVENT_H
#define GAMEOVEREVENT_H
#include "common/include/AbstractEvent.h"
#include "common/include/Event.h"
#include <vector>
#include <map>


class GameOverEvent :  public AbstractEvent {
public:
    updateEventType eventType;
    int idPlayer;
    std::map<std::string, std::vector<int>> highscores;
    GameOverEvent (updateEventType eventType, int idPlayer,
                            std::map<std::string, std::vector<int>>& names);
    void runHandler(CGame& game) override;
    updateEventType getEventType();
    std::string getSerialization() override;
};


#endif //GAME_H_GAMEOVEREVENT_H
