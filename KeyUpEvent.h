#ifndef KEYUPEVENT_H
#define KEYUPEVENT_H

#include "AbstractEvent.h"

class KeyUpEvent: public AbstractEvent {
public:
    void runHandler() override;
};

#endif
