#ifndef ABSTRACTEVENT_H
#define ABSTRACTEVENT_H

#include "GameStage.h"

class AbstractEvent {
public:
    virtual void runHandler(GameStage& gameStage) = 0;
    virtual ~AbstractEvent() = default;

    virtual bool thisIsTheQuitEvent();
};

#endif
