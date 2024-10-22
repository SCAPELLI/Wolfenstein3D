

#ifndef CAMERA_CPP_CHANGEWEAPONEVENT_H
#define CAMERA_CPP_CHANGEWEAPONEVENT_H
#include "common/include/AbstractEvent.h"
#include "common/include/Event.h"

class ChangeWeaponEvent  : public AbstractEvent{

public:
    int idPlayer;
    int type; // o tipo???
    ChangeWeaponEvent (int idPlayer, int type);
    void runHandler(GameStage& game) override;
    void runHandler(CGame& renderer) override;
    std::string getSerialization() override;
};


#endif //CAMERA_CPP_CHANGEWEAPONEVENT_H
