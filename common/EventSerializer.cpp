#include "EventSerializer.h"

#include "../common/Event.h"

#include "../common/ServerEvents/AmmoChangeEvent.h"
#include "../common/ServerEvents/ChangeWeaponEvent.h"
#include "../common/ServerEvents/CreateMapEvent.h"
#include "../common/ServerEvents/DespawnEvent.h"
#include "../common/ServerEvents/DoorOpenedEvent.h"
#include "../common/ServerEvents/GameOverEvent.h"
#include "../common/ServerEvents/HealthChangeEvent.h"
#include "../common/ServerEvents/KillEvent.h"
#include "../common/ServerEvents/PickUpKeyEvent.h"
#include "../common/ServerEvents/PickUpWeaponEvent.h"
#include "../common/ServerEvents/PositionEvent.h"
#include "../common/ServerEvents/ScoreChangeEvent.h"
#include "../common/ServerEvents/SpawnEvent.h"
#include "../common/ServerEvents/SpawnNotMovableEvent.h"
#include "../common/MovementEvent.h"
#include "../common/OpenDoorEvent.h"
#include "../common/QuitEvent.h"
#include "../common/ShootingEvent.h"
#include "../common/TurnEvent.h"

#include "Constants.h"

Event EventSerializer::createMovementEvent(std::string eventString) {
    //EEEPPPF o EEEPPPB
    //direction (1 byte)
    int playerId = std::stoi(eventString.substr (3, 3));
    MovementDirection direction;
    switch (eventString[6]) {
        case 'F':
            direction = FORWARD;
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
    return Event(&event, DoorOpenedEventType);
}

Event EventSerializer::createGameOverEvent(std::string eventString) {
    //EEEPPP
    int playerId = std::stoi(eventString.substr (3, 3));

    GameOverEvent event(GameOverEventType, playerId);
    return Event(&event, GameOverEventType);
}

Event EventSerializer::createPositionEvent(std::string eventString) {
    //EEEPPPX...XY...Y
    //x (20 bytes), y (20 bytes)
    int playerId = std::stoi(eventString.substr (3, 3));
    double x = std::stod(eventString.substr(6, 20));
    double y = std::stod(eventString.substr(26, 20));

    PositionEvent event(PositionEventType,playerId, x, y);
    return Event(&event, PositionEventType);
}

Event EventSerializer::createAmmoChangeEvent(std::string eventString) {
    //EEEBBBBBBBBB
    //ammo (9 bytes)
    int ammo = std::stoi(eventString.substr (3, 9));

    AmmoChangeEvent event(AmmoChangeType, ammo);
    return Event(&event, AmmoChangeType);
}

Event EventSerializer::createChangeWeaponEvent(std::string eventString) {
    //EEEPPPTTT
    //type (3 bytes)
    int playerId = std::stoi(eventString.substr (3, 3));
    int type = std::stoi(eventString.substr (6, 3));

    ChangeWeaponEvent event(playerId, type);
    return Event(&event, ChangeWeaponType);
}

std::string EventSerializer::serialize(ChangeWeaponEvent& event) {
    std::string playerId = std::to_string(event.idPlayer);
    addZerosToLeft(playerId, 3);

    std::string type = std::to_string(event.type);
    addZerosToLeft(type, 3);

    return AMMO_CHANGE_EVENT_STRING + playerId + type;
}

Event EventSerializer::createCreateMapEvent(std::string eventString) {
    //EEEHHHHHHWWWWWWSSS[PPPXXXXXXYYYYYY]
    //H: height (6 bytes)
    //W: width  (6 bytes)
    //S: number of players (3 bytes)
    //P: playerId (3 bytes)
    //X: pos X (6 bytes)
    //Y: pos Y (6 bytes)

    int height = std::stoi(eventString.substr (3, 6));
    int width = std::stoi(eventString.substr (9, 6));
    int numberOfPlayers = std::stoi(eventString.substr (15, 3));

    std::map<int, std::map<int, int>> startingLocations;
    CreateMapEvent event(CreateMapType, width , height);

    int p = 18;
    for (int i = 0; i < numberOfPlayers; ++i) {
        int playerId = std::stoi(eventString.substr (p + (i*3), 3));
        int x = std::stoi(eventString.substr (p + (i*3) + 3, 6));
        int y = std::stoi(eventString.substr (p + (i*3) + 9, 6));
        event.startingLocations[playerId].first=x;
        event.startingLocations[playerId].second=y;
    }
    return Event(&event, CreateMapType);
}

std::string EventSerializer::serialize(CreateMapEvent& event) {
    std::string witdh = std::to_string(event.width);
    addZerosToLeft(witdh, 6);

    std::string height = std::to_string(event.height);
    addZerosToLeft(height, 6);

    std::string numberOfPlayers = std::to_string(event.startingLocations.size());
    addZerosToLeft(numberOfPlayers, 3);

    std::string response = CREATE_MAP_EVENT_STRING + witdh + height + numberOfPlayers;

    for (auto& player: event.startingLocations) {
        std::string playerId = std::to_string(player.first);
        addZerosToLeft(playerId, 3);
        std::string x = std::to_string(player.second.first);
        addZerosToLeft(x, 6);
        std::string y = std::to_string(player.second.second);
        addZerosToLeft(y, 6);
        response.append(playerId).append(x).append(y);
    }
    return response;
}

Event EventSerializer::createDespawnEvent(std::string eventString) {
    //EEEIIITTT
    //id (3 bytes)
    //type (3 bytes)
    int id = std::stoi(eventString.substr (3, 3));
    int type = std::stoi(eventString.substr (6, 3));

    DespawnEvent event(DespawnEventType, id, type);
    return Event(&event, DespawnEventType);
}

std::string EventSerializer::serialize(DespawnEvent& event) {
    std::string id = std::to_string(event.id);
    addZerosToLeft(id, 3);

    std::string type = std::to_string(event.type);
    addZerosToLeft(type, 3);

    return DESPAWN_EVENT_STRING + id + type;
}

Event EventSerializer::createDoorOpenedEvent(std::string eventString) {
    //EEEXXXXXXYYYYYY
    //x (6 bytes)
    //y (6 bytes)
    int x = std::stoi(eventString.substr (3, 6));
    int y = std::stoi(eventString.substr (9, 15));

    DoorOpenedEvent event(DoorOpenedEventType, x, y);
    return Event(&event, DespawnEventType);
}

std::string EventSerializer::serialize(DoorOpenedEvent& event) {
    std::string x = std::to_string(event.x);
    addZerosToLeft(x, 6);

    std::string y = std::to_string(event.y);
    addZerosToLeft(y, 6);

    return DESPAWN_EVENT_STRING + x + y;
}

Event EventSerializer::createHealthChangeEvent(std::string eventString) {
    //EEEXXXXXXYYYYYY
    //health (6 bytes)
    //playerId (3 bytes)
    int health = std::stoi(eventString.substr (3, 9));
    int playerId = std::stoi(eventString.substr (9, 12));

    HealthChangeEvent event(HealthChangeType, health);
    event.idPlayer = playerId;
    return Event(&event, HealthChangeType);
}

std::string EventSerializer::serialize(HealthChangeEvent& event) {
    std::string health = std::to_string(event.health);
    addZerosToLeft(health, 6);

    std::string playerId = std::to_string(event.idPlayer);
    addZerosToLeft(playerId, 3);

    return HEALTH_CHANGE_EVENT_STRING + health + playerId;
}

Event EventSerializer::createKillEvent(std::string eventString) {
    //EEEPPP
    //playerId (3 bytes)
    int playerId = std::stoi(eventString.substr (3, 3));

    KillEvent event(KillEventType, playerId);
    return Event(&event, KillEventType);
}

std::string EventSerializer::serialize(KillEvent& event) {
    std::string playerId = std::to_string(event.idPlayer);
    addZerosToLeft(playerId, 3);

    return KILL_EVENT_STRING + playerId;
}

Event EventSerializer::createPickUpKeyEvent(std::string eventString) {
    //EEE
    PickUpKeyEvent event(PickUpKeyType);
    return Event(&event, PickUpKeyType);
}

std::string EventSerializer::serialize(PickUpKeyEvent& event) {
    return PICK_UP_KEY_EVENT_STRING;
}

Event EventSerializer::createPickUpWeaponEvent(std::string eventString) {
    //EEEPPP
    int playerId = std::stoi(eventString.substr (3, 6));

    PickUpKeyEvent event(PickUpWeaponType);
    return Event(&event, PickUpWeaponType);
}

std::string EventSerializer::serialize(PickUpWeaponEvent& event) {
    std::string response = std::to_string(event.uniqueId);
    addZerosToLeft(response, 3);

    return PICK_UP_WEAPON_EVENT_STRING + response;
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

std::string EventSerializer::serialize(AmmoChangeEvent& event) {
    std::string ammo = std::to_string(event.ammo);
    addZerosToLeft(ammo, 9);

    return AMMO_CHANGE_EVENT_STRING + ammo;
}

std::string EventSerializer::serialize(MovementEvent& event) {
    std::string playerId = std::to_string(event.idPlyr);
    addZerosToLeft(playerId, 3);

    std::string direction;
    if (event.direction == FORWARD) direction = 'F';
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

std::string EventSerializer::serialize(KillEvent& event) {
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
