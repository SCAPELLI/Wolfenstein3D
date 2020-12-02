#ifndef KEYRIGHTEVENT_H
#define KEYRIGHTEVENT_H

#include "AbstractEvent.h"

class KeyRightEvent: public AbstractEvent {
public:
    void runHandler() override;
};

#endif
