#ifndef KEYDOWNEVENT_H
#define KEYDOWNEVENT_H

#include "AbstractEvent.h"

class KeyDownEvent: public AbstractEvent {
public:
    void runHandler() override;
};

#endif
