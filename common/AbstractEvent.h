#ifndef ABSTRACTEVENT_H
#define ABSTRACTEVENT_H
#include "Constants.h"

#include <string>

class GameStage;
class CGame;
class ProtectedEventsQueue;

class AbstractEvent {
    updateEventType eventType;
public:
    virtual void runHandler(GameStage& gameStage) {}
    virtual void runHandler(CGame& game) {}
    virtual updateEventType getEventType();
    virtual std::string getSerialization();

    virtual ~AbstractEvent() = default;

    virtual bool thisIsTheQuitEvent();
};

#endif
