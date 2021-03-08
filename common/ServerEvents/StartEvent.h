

#ifndef STARTEVENT_H
#define STARTEVENT_H
#include "common/include/Event.h"

class CGame;

class StartEvent : public AbstractEvent{
    public:
        updateEventType eventType;
        explicit StartEvent(updateEventType eventType);
        std::string getSerialization() override;
        bool thisIsTheStartEvent() override;
        updateEventType getEventType();
};


#endif //STARTEVENT_H
