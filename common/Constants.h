

#ifndef CAMERA_CPP_CONSTANTS_H
#define CAMERA_CPP_CONSTANTS_H


enum updateEventType {KillEventType, ShootingEventType,
    PositionEventType, GameOverEventType,
    TurnEventType, DoorOpenedEventType, SpawnEventType,
    AmmoChangeType, ChangeWeaponType, DespawnEventType,
    HealthChangeType, PickUpKeyType, PickUpWeaponType,
    ScoreChangeType, SpawnNotMovableType, MovementEventType};

#define PLAYER_ID 1
#define TILE 32

#endif //CAMERA_CPP_CONSTANTS_H
