#ifndef QUITEVENT_H
#define QUITEVENT_H

#include "AbstractEvent.h"
#include <map>
#include <vector>
/*Evento que indica salir de la aplicación*/
class QuitEvent: public AbstractEvent {
public:
    std::map<std::string, std::vector<int>> highscore;
    int playerId;

    QuitEvent(int playerId);
    void runHandler(GameStage& gameStage) override;
    bool thisIsTheQuitEvent() override;
    std::string getSerialization() override;
};

#endif
