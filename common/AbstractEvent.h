#ifndef ABSTRACTEVENT_H
#define ABSTRACTEVENT_H

#include <string>

class GameStage;
class CGame;
class ProtectedEventsQueue;

class AbstractEvent {
public:
    virtual void runHandler(GameStage& gameStage) {}
    virtual void runHandler(CGame& game) {}
    virtual std::string getSerialization();

    virtual ~AbstractEvent() = default;

    virtual bool thisIsTheQuitEvent();
};

#endif
