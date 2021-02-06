

#ifndef DOOROPENEDEVENT_H
#define DOOROPENEDEVENT_H
#include "../AbstractEvent.h"


class DoorOpenedEvent  : public AbstractEvent{
public:
    int uniqueId;
    explicit DoorOpenedEvent(int uniqueId);
};


#endif //DOOROPENEDEVENT_H
