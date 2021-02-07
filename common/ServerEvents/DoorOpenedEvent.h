

#ifndef DOOROPENEDEVENT_H
#define DOOROPENEDEVENT_H
#include "../AbstractEvent.h"
#include "Event.h"


class DoorOpenedEvent  : public AbstractEvent{
public:
    int uniqueId;
    updateEventType eventType;
    explicit DoorOpenedEvent (updateEventType eventType, int uniqueId);
    updateEventType getEventType();
};


#endif //DOOROPENEDEVENT_H
