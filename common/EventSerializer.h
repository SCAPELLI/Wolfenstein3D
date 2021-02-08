#ifndef EVENTSERIALIZER_H
#define EVENTSERIALIZER_H

#include <string>

const int MOVEMENT_EVENT = 1;
const std::string MOVEMENT_EVENT_STRING = "001";

const int TURN_EVENT = 2;
const std::string TURN_EVENT_STRING = "002";

const int SHOOTING_EVENT = 3;
const std::string SHOOTING_EVENT_STRING = "003";

const int OPEN_DOOR_EVENT = 5;
const std::string OPEN_DOOR_EVENT_STRING = "005";

const int GAME_OVER_EVENT = 14;
const std::string GAME_OVER_EVENT_STRING = "014";

const int POSITION_EVENT = 15;
const std::string POSITION_EVENT_STRING = "015";

class Event;
class MovementEvent;
class TurnEvent;
class OpenDoorEvent;
class ShootingEvent;
class PositionEvent;
class KillEvent;
class GameOverEvent;

class EventSerializer {
public:
    static Event createMovementEvent(std::string eventString);
    static Event createTurnEvent(std::string eventString);
    static Event createShootingEvent(std::string eventString);
    static Event createOpenDoorEvent(std::string eventString);
    static Event createGameOverEvent(std::string eventString);
    static Event createPositionEvent(std::string eventString);
    static Event deserialize(std::string eventString);

    static void addZerosToLeft(std::string& string, int finalSize);
    static void addZerosToRight(std::string& string, int finalSize);

    static std::string serialize(MovementEvent& event);
    static std::string serialize(TurnEvent& event);
    static std::string serialize(ShootingEvent& event);
    static std::string serialize(PositionEvent& event);
    static std::string serialize(OpenDoorEvent& event);
    static std::string serialize(KillEvent& event);
    static std::string serialize(GameOverEvent& event);
    static std::string serialize(Event& event);
};

#endif
