#ifndef EVENTSERIALIZER_H
#define EVENTSERIALIZER_H

#include <string>
/* Serializador de eventos*/
const int AMMO_CHANGE_EVENT = 0;
const std::string AMMO_CHANGE_EVENT_STRING = "000";

const int CHANGE_WEAPON_EVENT = 1;
const std::string CHANGE_WEAPON_EVENT_STRING = "001";

const int CREATE_MAP_EVENT = 2;
const std::string CREATE_MAP_EVENT_STRING = "002";

const int DESPAWN_EVENT = 3;
const std::string DESPAWN_EVENT_STRING = "003";

const int DOOR_OPENED_EVENT = 4;
const std::string DOOR_OPENED_EVENT_STRING = "004";

const int GAME_OVER_EVENT = 5;
const std::string GAME_OVER_EVENT_STRING = "005";

const int HEALTH_CHANGE_EVENT = 6;
const std::string HEALTH_CHANGE_EVENT_STRING = "006";

const int KILL_EVENT = 7;
const std::string KILL_EVENT_STRING = "007";

const int PICK_UP_KEY_EVENT = 8;
const std::string PICK_UP_KEY_EVENT_STRING = "008";

const int PICK_UP_WEAPON_EVENT = 9;
const std::string PICK_UP_WEAPON_EVENT_STRING = "009";

const int POSITION_EVENT = 10;
const std::string POSITION_EVENT_STRING = "10";

const int SCORE_CHANGE_EVENT = 11;
const std::string SCORE_CHANGE_EVENT_STRING = "011";

const int SPAWN_EVENT = 12;
const std::string SPAWN_EVENT_STRING = "012";

const int SPAWN_NOT_MOVABLE_EVENT = 13;
const std::string SPAWN_NOT_MOVABLE_EVENT_STRING = "013";

const int MOVEMENT_EVENT = 14;
const std::string MOVEMENT_EVENT_STRING = "014";

const int OPEN_DOOR_EVENT = 15;
const std::string OPEN_DOOR_EVENT_STRING = "015";

const int QUIT_EVENT = 16;
const std::string QUIT_EVENT_STRING = "016";

const int SHOOTING_EVENT = 17;
const std::string SHOOTING_EVENT_STRING = "017";

const int TURN_EVENT = 18;
const std::string TURN_EVENT_STRING = "018";

class Event;
class AmmoChangeEvent;
class ChangeWeaponEvent;
class CreateMapEvent;
class DespawnEvent;
class DoorOpenedEvent;
class GameOverEvent;
class HealthChangeEvent;
class KillEvent;
class PickUpKeyEvent;
class PickUpWeaponEvent;
class PositionEvent;
class ScoreChangeEvent;
class SpawnEvent;
class SpawnNotMovableEvent;
class MovementEvent;
class OpenDoorEvent;
class QuitEvent;
class ShootingEvent;
class TurnEvent;

class EventSerializer {
public:
    static Event createAmmoChangeEvent(std::string eventString);
    static Event createChangeWeaponEvent(std::string eventString);
    static Event createCreateMapEvent(std::string eventString);
    static Event createDespawnEvent(std::string eventString);
    static Event createDoorOpenedEvent(std::string eventString);
    static Event createGameOverEvent(std::string eventString);
    static Event createHealthChangeEvent(std::string eventString);
    static Event createKillEvent(std::string eventString);
    static Event createPickUpKeyEvent(std::string eventString);
    static Event createPickUpWeaponEvent(std::string eventString);
    static Event createPositionEvent(std::string eventString);
    static Event createScoreChangeEvent(std::string eventString);
    static Event createSpawnNotMovableEvent(std::string eventString);
    static Event createMovementEvent(std::string eventString);
    static Event createOpenDoorEvent(std::string eventString);
    static Event createQuitEvent(std::string eventString);
    static Event createShootingEvent(std::string eventString);
    static Event createTurnEvent(std::string eventString);

    static Event deserialize(std::string eventString);

    static void addZerosToLeft(std::string& string, int finalSize);
    static void addZerosToRight(std::string& string, int finalSize);


    static std::string serialize(AmmoChangeEvent& event);
    static std::string serialize(ChangeWeaponEvent& event);
    static std::string serialize(CreateMapEvent& event);
    static std::string serialize(DespawnEvent& event);
    static std::string serialize(DoorOpenedEvent& event);
    static std::string serialize(GameOverEvent& event);
    static std::string serialize(HealthChangeEvent& event);
    static std::string serialize(KillEvent& event);
    static std::string serialize(PickUpKeyEvent& event);
    static std::string serialize(PickUpWeaponEvent& event);
    static std::string serialize(PositionEvent& event);
    static std::string serialize(ScoreChangeEvent& event);
    static std::string serialize(SpawnNotMovableEvent& event);
    static std::string serialize(MovementEvent& event);
    static std::string serialize(OpenDoorEvent& event);
    static std::string serialize(QuitEvent& event);
    static std::string serialize(ShootingEvent& event);
    static std::string serialize(TurnEvent& event);
    static std::string serialize(Event& event);
};

#endif
