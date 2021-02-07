
#include "GameOverEvent.h"
#include "cliente/CGame.h"
#include "Event.h"

GameOverEvent::GameOverEvent (GameOverEvent& gameOverEvent){}

GameOverEvent::GameOverEvent (updateEventType eventType, int idPlayer) : idPlayer(idPlayer), eventType(eventType){}

void GameOverEvent::runHandler(CGame& game){

}

updateEventType GameOverEvent::getEventType() {
    return eventType;
}
