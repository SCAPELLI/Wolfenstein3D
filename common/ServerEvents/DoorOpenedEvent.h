

#ifndef DOOROPENEDEVENT_H
#define DOOROPENEDEVENT_H
#include "common/include/AbstractEvent.h"
#include "common/include/Event.h"


class DoorOpenedEvent  : public AbstractEvent{
public:
    int x, y;
    updateEventType eventType;
    explicit DoorOpenedEvent (updateEventType eventType, int x, int y);
    updateEventType getEventType();
    void runHandler(CGame& renderer) override;
    std::string getSerialization() override;

};


#endif //DOOROPENEDEVENT_H
