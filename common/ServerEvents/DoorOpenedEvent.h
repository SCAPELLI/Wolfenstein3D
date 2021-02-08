

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
    void runHandler(CGame& renderer) override;
    //std::string getSerialization() override;
};


#endif //DOOROPENEDEVENT_H
