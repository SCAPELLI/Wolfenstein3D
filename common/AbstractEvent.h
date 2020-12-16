#ifndef ABSTRACTEVENT_H
#define ABSTRACTEVENT_H

class GameStage;
class CGame;
class ProtectedEventsQueue;

class AbstractEvent {
public:
    virtual void runHandler(GameStage& gameStage) {}
    virtual void runHandler(CGame& game) {}

    virtual ~AbstractEvent() = default;

    virtual bool thisIsTheQuitEvent();
};

#endif
