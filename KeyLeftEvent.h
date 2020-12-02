#ifndef KEYLEFTEVENT_H
#define KEYLEFTEVENT_H

#include "AbstractEvent.h"

class KeyLeftEvent: public AbstractEvent {
public:
    void runHandler() override;
};

#endif
