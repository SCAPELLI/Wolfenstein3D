#include "PlayerEvent.h"
#include "ServerEvents/SpawnEvent.h"
#include "Player.h"
#include "ServerEvents/PositionEvent.h"
#include "ServerEvents/KillEvent.h"

PlayerEvent::PlayerEvent() {}

void PlayerEvent::addItem(Player* player, int x, int y){
    AbstractEvent* event = new PositionEvent(player->getId(), x, y);
    events.insert(std::make_pair(player->getId(), event));
}

void PlayerEvent::addItem(Player* player){
    AbstractEvent* event = new KillEvent(player->getId());
    events.insert(std::make_pair(player->getId(), event));
}

void PlayerEvent::removeItem(Player* player){
    events.erase(player->getId());
}
