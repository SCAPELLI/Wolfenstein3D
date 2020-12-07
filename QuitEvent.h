#ifndef QUITEVENT_H
#define QUITEVENT_H

#include "AbstractEvent.h"

class QuitEvent: public AbstractEvent {
public:
    void runHandler(GameStage& gameStage) override;
    bool thisIsTheQuitEvent() override;
};

#endif
