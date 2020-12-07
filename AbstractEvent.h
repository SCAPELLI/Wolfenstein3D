#ifndef ABSTRACTEVENT_H
#define ABSTRACTEVENT_H

class GameStage;
class Renderer;
class ProtectedEventsQueue;

class AbstractEvent {
public:
    virtual void runHandler(GameStage& gameStage) {}
    virtual void runHandler(Renderer& renderer) {}

    virtual ~AbstractEvent() = default;

    virtual bool thisIsTheQuitEvent();
};

#endif
