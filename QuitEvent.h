#ifndef QUITEVENT_H
#define QUITEVENT_H

#include "AbstractEvent.h"

class QuitEvent: public AbstractEvent {
public:
    void runHandler() override;
    bool thisIsTheQuitEvent() override;
};

#endif
