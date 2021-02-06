#include "EventSerializer.h"
#include "../common/MovementEvent.h"
#include "../common/TurnEvent.h"
#include "../common/ShootingEvent.h"
#include "../common/OpenDoorEvent.h"
#include "../common/GameOverEvent.h"
#include "../common/PositionEvent.h"
#include "../common/Event.h"

Event EventSerializer::createMovementEvent(std::string eventString) {
    //EEEPPPF o EEEPPPB
    //direction (1 byte)
    int playerId = std::stoi(eventString.substr (3, 3));
    MovementDirection direction;
    switch (eventString[6]) {
        case 'F':
            direction = FOWARD;
            break;
        case 'B':
            direction = BACKWARD;
            break;
    }

    MovementEvent event(direction, playerId);
    return Event(&event, MovementEventType);
}

Event EventSerializer::createTurnEvent(std::string eventString) {
    //EEEPPPAAAAAAAAAA
    //angleVariation (10 bytes)
    int playerId = std::stoi(eventString.substr (3, 3));
    float angleVariation = std::stof(eventString.substr(6, 10));

    TurnEvent event(playerId, angleVariation);
    return Event(&event, TurnEventType);
}

Event EventSerializer::createShootingEvent(std::string eventString) {
    //EEEPPP
    int playerId = std::stoi(eventString.substr (3, 3));

    ShootingEvent event(playerId);
    return Event(&event, ShootingEventType);
}

Event EventSerializer::createOpenDoorEvent(std::string eventString) {
    //EEEPPPT o EEEPPPF
    //isOpen (1 byte)
    int playerId = std::stoi(eventString.substr (3, 3));
    bool isOpen = (eventString[6] == 'T');

    OpenDoorEvent event(playerId, isOpen);
    return Event(&event, OpenDoorType);
}

Event EventSerializer::createGameOverEvent(std::string eventString) {
    //EEEPPP
    int playerId = std::stoi(eventString.substr (3, 3));

    GameOverEvent event(playerId);
    return Event(&event, GameOverEventType);
}

Event EventSerializer::createPositionEvent(std::string eventString) {
    //EEEPPPX...XY...Y
    //x (20 bytes), y (20 bytes)
    int playerId = std::stoi(eventString.substr (3, 3));
    double x = std::stod(eventString.substr(6, 20));
    double y = std::stod(eventString.substr(26, 20));

    PositionEvent event(playerId, x, y);
    return Event(&event, PositionEventType);
}

Event EventSerializer::deserialize(std::string eventString) {
    // ID (3 bytes); playerId (3 bytes) (ojo, no siempre hay playerId);
    Event event;
    int eventId = stoi(eventString.substr(0,3));

    switch (eventId) {
        case MOVEMENT_EVENT:
            return createMovementEvent(eventString);
            break;
        case TURN_EVENT:
            return createTurnEvent(eventString);
            break;
        case SHOOTING_EVENT:
            return createShootingEvent(eventString);
            break;
        case OPEN_DOOR_EVENT:
            return createOpenDoorEvent(eventString);
            break;
        case GAME_OVER_EVENT:
            return createGameOverEvent(eventString);
            break;
        case POSITION_EVENT:
            return createPositionEvent(eventString);
            break;
        default:
            return event;
            break;
    }
}
void EventSerializer::addZerosToLeft(std::string& string, int finalSize) {
    while (string.length() != finalSize) {
        string.insert(string.begin(),'0');
    }
}
void EventSerializer::addZerosToRight(std::string& string, int finalSize) {
    while (string.length() != finalSize) {
        string.insert(string.end(),'0');
    }
}

std::string EventSerializer::serialize(MovementEvent& event) {
    std::string playerId = std::to_string(event.idPlyr);
    addZerosToLeft(playerId, 3);

    std::string direction;
    if (event.direction == FOWARD) direction = 'F';
    if (event.direction == BACKWARD) direction = 'B';

    return MOVEMENT_EVENT_STRING + playerId + direction;
}

std::string EventSerializer::serialize(TurnEvent& event) {
    std::string playerId = std::to_string(event.idPlayer);
    addZerosToLeft(playerId, 3);

    std::string angleVariation = std::to_string(event.degrees);
    addZerosToRight(angleVariation, 20);

    return TURN_EVENT_STRING + playerId + angleVariation;
}

std::string EventSerializer::serialize(ShootingEvent& event) {
    std::string playerId = std::to_string(event.idPlayer);
    addZerosToLeft(playerId, 3);

    return SHOOTING_EVENT_STRING + playerId;
}

std::string EventSerializer::serialize(PositionEvent& event) {
    std::string playerId = std::to_string(event.playerId);
    addZerosToLeft(playerId, 3);

    std::string x = std::to_string(event.x);
    addZerosToRight(x, 20);
    std::string y = std::to_string(event.y);
    addZerosToRight(y, 20);

    return POSITION_EVENT_STRING + playerId + x + y;
}

std::string EventSerializer::serialize(OpenDoorEvent& event) {
    std::string playerId = std::to_string(event.idPlayer);
    addZerosToLeft(playerId, 3);

    std::string opened;
    if (event.opened)
        opened = 'T';
    else
        opened = 'F';
    return OPEN_DOOR_EVENT_STRING + playerId + opened;
}

std::string EventSerializer::serialize(LifeDecrementEvent& event) {
    return "";
}

std::string EventSerializer::serialize(GameOverEvent& event) {
    std::string playerId = std::to_string(event.idPlayer);
    addZerosToLeft(playerId, 3);

    return GAME_OVER_EVENT_STRING + playerId;
}

std::string EventSerializer::serialize(Event& event) {
    return event.getSerialization();
}
