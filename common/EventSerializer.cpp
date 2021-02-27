#include <algorithm>
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
#include "../common/ServerEvents/ScoreChangeEvent.h"
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
    //EEEPPPA..A
    //angleVariation (20 bytes)
    int playerId = std::stoi(eventString.substr (3, 3));
    std::setlocale(LC_ALL, "en_US.UTF-8");
    double angleVariation = std::stod(eventString.substr(6, 20));

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
    std::map<std::string, std::vector<int>> highscores;
    GameOverEvent event(GameOverEventType, playerId, highscores); //hardcode
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
    //EEEIIIBBBBBBBBB
    //id (3 bytes)
    //ammo (9 bytes)
    int id = std::stoi(eventString.substr (3, 3));
    int ammo = std::stoi(eventString.substr (6, 9));

    AmmoChangeEvent event(AmmoChangeType, id, ammo);
    return Event(&event, AmmoChangeType);
}

Event EventSerializer::createChangeWeaponEvent(std::string eventString) {
    //PPPTTT
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
    std::string width = std::to_string(event.width);
    addZerosToLeft(width, 6);

    std::string height = std::to_string(event.height);
    addZerosToLeft(height, 6);

    std::string numberOfPlayers = std::to_string(event.startingLocations.size());
    addZerosToLeft(numberOfPlayers, 3);

    std::string response = CREATE_MAP_EVENT_STRING + height + width + numberOfPlayers;

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

std::string EventSerializer::serialize(SpawnNotMovableEvent& event) {
    // EEETTTXXXYYY
    // type 3 bytes
    // x,y pos 3 bytes
    std::string type = std::to_string(event.type);
    addZerosToLeft(type, 3);
    std::string posX = std::to_string(event.posX);
    addZerosToLeft(posX, 3);
    std::string posY = std::to_string(event.posY);
    addZerosToLeft(posY, 3);

    return SPAWN_NOT_MOVABLE_EVENT_STRING + type + posX + posY;
}

std::string EventSerializer::serialize(SpawnEvent& event) {
    // EEEIIITTTXXXYYY
    //id 3 bytes
    // type 3 bytes
    // x,y pos 3 bytes
    std::string id = std::to_string(event.id);
    addZerosToLeft(id, 3);
    std::string type = std::to_string(event.type);
    addZerosToLeft(type, 3);
    std::string posX = std::to_string(event.posX);
    addZerosToLeft(posX, 3);
    std::string posY = std::to_string(event.posY);
    addZerosToLeft(posY, 3);

    return SPAWN_EVENT_STRING + id + type + posX + posY;
}

Event EventSerializer::createSpawnEvent(std::string eventString) {
    int id = std::stoi(eventString.substr (3, 3));
    int t = std::stoi(eventString.substr (6, 3));
    int x = std::stoi(eventString.substr (9, 3));
    int y = std::stoi(eventString.substr (12, 3));

    SpawnEvent event(SpawnEventType, id, t, x, y);
    return Event(&event, SpawnEventType);
}

Event EventSerializer::createScoreChangeEvent(std::string eventString) {
    int id = std::stoi(eventString.substr (3, 3));
    int score = std::stoi(eventString.substr (6, 4));
    ScoreChangeEvent event(ScoreChangeType, id, score);
    return Event(&event, ScoreChangeType);
}
std::string EventSerializer::serialize(ScoreChangeEvent& event) {
    //      EEEIIISSSS
    //    int idPlayer 3 bytes
    //    int score;    4 bytes;
    std::string id = std::to_string(event.idPlayer);
    addZerosToLeft(id, 3);
    std::string score = std::to_string(event.score);
    addZerosToLeft(score, 4);
    return SCORE_CHANGE_EVENT_STRING + id + score;
}
Event EventSerializer::createSpawnNotMovableEvent(std::string eventString) {
    int t = std::stoi(eventString.substr (3, 3));
    int x = std::stoi(eventString.substr (6, 3));
    int y = std::stoi(eventString.substr (9, 3));

    SpawnNotMovableEvent event(SpawnNotMovableType, t, x, y);
    return Event(&event, SpawnNotMovableType);
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
    //EEEIIIHHHHHH
    //health (6 bytes)
    //playerId (3 bytes)
    int playerId = std::stoi(eventString.substr (3, 3));
    int health = std::stoi(eventString.substr (6, 6));

    HealthChangeEvent event(HealthChangeType, playerId, health);
    event.idPlayer = playerId;
    return Event(&event, HealthChangeType);
}

std::string EventSerializer::serialize(HealthChangeEvent& event) {
    std::string idPLayer = std::to_string(event.idPlayer);
    addZerosToLeft(idPLayer, 3);

    std::string health = std::to_string(event.health);
    addZerosToLeft(health, 6);

    return HEALTH_CHANGE_EVENT_STRING + idPLayer + health;
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
    //EEEIII
    int playerId = std::stoi(eventString.substr (3, 6));
    PickUpKeyEvent event(PickUpKeyType, playerId);
    return Event(&event, PickUpKeyType);
}

std::string EventSerializer::serialize(PickUpKeyEvent& event) {
    std::string playerId = std::to_string(event.idPlayer);
    addZerosToLeft(playerId, 3);
    return PICK_UP_KEY_EVENT_STRING + playerId;
}

Event EventSerializer::createPickUpWeaponEvent(std::string eventString) {
    //EEEPPP
    int playerId = std::stoi(eventString.substr (3, 6));

    PickUpKeyEvent event(PickUpWeaponType, playerId);
    return Event(&event, PickUpWeaponType);
}

std::string EventSerializer::serialize(PickUpWeaponEvent& event) {
    std::string idPlayer = std::to_string(event.idPlayer);
    std::string response = std::to_string(event.uniqueId);
    addZerosToLeft(response, 3);

    return PICK_UP_WEAPON_EVENT_STRING + idPlayer + response;
}

Event EventSerializer::deserialize(std::string eventString) {
    // ID (3 bytes); playerId (3 bytes) (ojo, no siempre hay playerId);
    Event event;
    int eventId = stoi(eventString.substr(0,3));

    switch (eventId) {
        case MOVEMENT_EVENT:
            return createMovementEvent(eventString);
        case TURN_EVENT:
            return createTurnEvent(eventString);
        case SHOOTING_EVENT:
            return createShootingEvent(eventString);
        case OPEN_DOOR_EVENT:
            return createOpenDoorEvent(eventString);
        case GAME_OVER_EVENT:
            return createGameOverEvent(eventString);
        case POSITION_EVENT:
            return createPositionEvent(eventString);
        case SPAWN_NOT_MOVABLE_EVENT:
            return createSpawnNotMovableEvent(eventString);
        case CREATE_MAP_EVENT:
            return createCreateMapEvent(eventString);
        case SPAWN_EVENT:
            return createSpawnEvent(eventString);
        case AMMO_CHANGE_EVENT:
            return  createAmmoChangeEvent(eventString);
        case CHANGE_WEAPON_EVENT:
            return createChangeWeaponEvent(eventString);
        case DESPAWN_EVENT:
            return createDespawnEvent(eventString);
        case DOOR_OPENED_EVENT:
            return createDoorOpenedEvent(eventString);
        case HEALTH_CHANGE_EVENT:
            return createHealthChangeEvent(eventString);
        case KILL_EVENT:
            return createKillEvent(eventString);
        case PICK_UP_KEY_EVENT:
            return createPickUpKeyEvent(eventString);
        case PICK_UP_WEAPON_EVENT:
            return createPickUpWeaponEvent(eventString);
        case SCORE_CHANGE_EVENT:
            return createScoreChangeEvent(eventString);
        default:
            return event;
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
    std::string id = std::to_string(event.idPlayer);
    addZerosToLeft(id, 3);
    std::string ammo = std::to_string(event.ammo);
    addZerosToLeft(ammo, 9);

    return AMMO_CHANGE_EVENT_STRING + id + ammo;
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
    std::replace(angleVariation.begin(),angleVariation.end(), ',', '.');
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


std::string EventSerializer::serialize(GameOverEvent& event) {
    std::string playerId = std::to_string(event.idPlayer);
    addZerosToLeft(playerId, 3);

    return GAME_OVER_EVENT_STRING + playerId;
}

std::string EventSerializer::serialize(Event& event) {
    return event.getSerialization();
}
