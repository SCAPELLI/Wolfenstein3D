#ifndef ABSTRACTEVENT_H
#define ABSTRACTEVENT_H

class AbstractEvent {
public:
    virtual void runHandler() = 0;
    virtual ~AbstractEvent() = default;

    virtual bool thisIsTheQuitEvent();
};

#endif
