#include "common/include/Event.h"
#include "common/include/QuitEvent.h"
#include "common/include/MovementEvent.h"
#include "common/include/TurnEvent.h"
#include "common/ServerEvents/SpawnEvent.h"

/*----------*/
#include "common/ServerEvents/KillEvent.h"
#include "common/ServerEvents/GameOverEvent.h"
#include "common/include/ShootingEvent.h"
#include "common/ServerEvents/PositionEvent.h"
#include "common/ServerEvents/DoorOpenedEvent.h"
#include "common/ServerEvents/ChangeWeaponEvent.h"
#include "common/ServerEvents/DespawnEvent.h"
#include "common/ServerEvents/SpawnNotMovableEvent.h"
#include "common/ServerEvents/ScoreChangeEvent.h"
#include "common/ServerEvents/HealthChangeEvent.h"
#include "common/ServerEvents/GameOverEvent.h"
#include "common/ServerEvents/AmmoChangeEvent.h"
#include "common/include/OpenDoorEvent.h"
#include "common/ServerEvents/CreateMapEvent.h"
#include "common/ServerEvents/PickUpKeyEvent.h"
#define PI 3.141592
/*----------*/


Event::Event(AbstractEvent* updateEvent, updateEventType eventType) {
    switch (eventType) {
        case KillEventType:
            event = new KillEvent(*(KillEvent*)updateEvent);
            break;
        case ShootingEventType:
            event = new ShootingEvent(*(ShootingEvent*)updateEvent);
            break;
        case PositionEventType:
            event = new PositionEvent(*(PositionEvent*)updateEvent);
            break;
        case GameOverEventType:
            event = new GameOverEvent(*(GameOverEvent*)updateEvent);
            break;
        case TurnEventType:
            event = new TurnEvent(*(TurnEvent*)updateEvent);
            break;
        case DoorOpenedEventType:
            event = new DoorOpenedEvent(*(DoorOpenedEvent*)updateEvent);
            break;
        case SpawnEventType:
            event = new SpawnEvent(*(SpawnEvent*)updateEvent);
            break;
        case DespawnEventType:
            event = new DespawnEvent(*(DespawnEvent*)updateEvent);
            break;
        case ChangeWeaponType:
            event = new ChangeWeaponEvent(*(ChangeWeaponEvent*)updateEvent);
            break;
        case SpawnNotMovableType:
            event = new SpawnNotMovableEvent(*(SpawnNotMovableEvent*)updateEvent);
            break;
        case ScoreChangeType:
            event = new ScoreChangeEvent(*(ScoreChangeEvent*)updateEvent);
            break;
        case AmmoChangeType:
            event = new AmmoChangeEvent(*(AmmoChangeEvent*)updateEvent);
            break;
        case HealthChangeType:
            event = new HealthChangeEvent(*(HealthChangeEvent*)updateEvent);
            break;
        case CreateMapType:
            event = new CreateMapEvent(*(CreateMapEvent*)updateEvent);
            break;
        case MovementEventType:
            event = new MovementEvent(*(MovementEvent*)updateEvent);
            break;
        case OpenDoorEventType:
            event = new OpenDoorEvent(*(OpenDoorEvent*)updateEvent);
            break;
        case QuitEventType:
            event = new QuitEvent(*(QuitEvent*)updateEvent);
            break;
        case PickUpKeyType:
            event = new PickUpKeyEvent(*(PickUpKeyEvent*)updateEvent);
            break;
        default:
            this->event = nullptr;
    }
}

Event::Event(SDL_Event& sdlEvent, int playerId) {
    switch (sdlEvent.type) {
        case SDL_QUIT:
            event = new QuitEvent(playerId);
            break;
        case SDL_KEYDOWN:
            event = keyCodeLookUp(sdlEvent, playerId);
            break;
        default:
            event = nullptr;
    }
}

AbstractEvent* Event::keyCodeLookUp(SDL_Event& sdlEvent, int playerId) {
    switch (sdlEvent.key.keysym.sym) {
        case SDLK_UP:
            return new MovementEvent(FORWARD, playerId);
        case SDLK_DOWN:
            return new MovementEvent(BACKWARD, playerId);
        case SDLK_LEFT:
            return new TurnEvent(playerId, PI/30);
        case SDLK_RIGHT:
            return new TurnEvent(playerId, -PI/30);
        case SDLK_SPACE:
            return new ShootingEvent(playerId);
        case SDLK_1:
            return new ChangeWeaponEvent(playerId, 0);
        case SDLK_2:
            return new ChangeWeaponEvent(playerId, 1);
        case SDLK_3:
            return new ChangeWeaponEvent(playerId, 2);
        case SDLK_4:
            return new ChangeWeaponEvent(playerId, 3);
        case SDLK_5:
            return new ChangeWeaponEvent(playerId, 4);
        case SDLK_e:
            return new OpenDoorEvent(playerId,0);
        default:
            return nullptr;
    }
}
Event::Event() {
    event = nullptr;
}
Event& Event::operator= (Event&& anotherEvent) noexcept {
    event = anotherEvent.event;
    anotherEvent.event = nullptr;
    return *this;
};
std::string Event::getSerialization() {
    if (event != nullptr) return event->getSerialization();
    else return "";
}
Event::Event(Event&& originalEvent) noexcept {
    event = originalEvent.event;
    originalEvent.event = nullptr;
}
void Event::runHandler(GameStage& gameStage) {
    if (event != nullptr) event->runHandler(gameStage);
}
/*-----------*/
void Event::runHandler(CGame& game) {
    if (event != nullptr) event->runHandler(game);
}
/*-----------*/
bool Event::thisIsTheQuitEvent() {
    if (event != nullptr) return event->thisIsTheQuitEvent();
    return false;
}
bool Event::thisIsAValidEvent() {
    return event != nullptr;
}
Event::~Event() {
    delete event;
}
