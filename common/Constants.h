

#ifndef CAMERA_CPP_CONSTANTS_H
#define CAMERA_CPP_CONSTANTS_H


enum updateEventType {KillEventType, ShootingEventType,
    PositionEventType, GameOverEventType,
    TurnEventType, DoorOpenedEventType, SpawnEventType,
    AmmoChangeType, ChangeWeaponType, DespawnEventType,
    HealthChangeType, PickUpKeyType, PickUpWeaponType,
    ScoreChangeType, SpawnNotMovableType, MovementEventType,
    CreateMapType, QuitEventType, OpenDoorEventType};

enum weaponName {Knife, Pistol, MachineGun, ChainGun, RocketLauncher};
#define PLAYER_ID 1
//#define PI 3.141592
#define WEAPONSGAP 49
#define TILE 32

#endif //CAMERA_CPP_CONSTANTS_H
