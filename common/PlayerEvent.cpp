#include "PlayerEvent.h"
#include "SpawnEvent.h"
#include "Player.h"
#include "PositionEvent.h"
#include "LifeDecrementEvent.h"

PlayerEvent::PlayerEvent() {}

void PlayerEvent::addItem(Player* player, int x, int y){
    AbstractEvent* event = new PositionEvent(player->getId(), x, y);
    events.insert(std::make_pair(player->getId(), event));
}

void PlayerEvent::addItem(Player* player){
    AbstractEvent* event = new LifeDecrementEvent(player->getId());
    events.insert(std::make_pair(player->getId(), event));
}

void PlayerEvent::removeItem(Player* player){
    events.erase(player->getId());
}
