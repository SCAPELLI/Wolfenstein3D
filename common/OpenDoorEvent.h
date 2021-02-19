
#ifndef OPENDOOREVENT_H
#define OPENDOOREVENT_H
#include "AbstractEvent.h"
class GameStage;

class OpenDoorEvent : public AbstractEvent {
public:
    int idPlayer;
    bool opened;
    OpenDoorEvent(int idPlayer, bool isOpen);
    //OpenDoorEvent(OpenDoorEvent& openDoorEvent);
    void changeStatusDoor(bool status);
    void runHandler(GameStage& renderer) override;
    std::string getSerialization() override;
    };


#endif //OPENDOOREVENT_H
