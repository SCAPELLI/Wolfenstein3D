

#ifndef CAMERA_CPP_CHANGEWEAPONEVENT_H
#define CAMERA_CPP_CHANGEWEAPONEVENT_H
#include "../AbstractEvent.h"

class ChangeWeaponEvent  : public AbstractEvent{
 int idPlayer;
 int uniqueId; // o tipo???
public:
    ChangeWeaponEvent(int idPlayer, int uniqueId);
};


#endif //CAMERA_CPP_CHANGEWEAPONEVENT_H
