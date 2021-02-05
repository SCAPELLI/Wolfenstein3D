

#include "MapEvent.h"
#include "SpawnEvent.h"

MapEvent::MapEvent() {}

void MapEvent::addItem(Item* item, int x, int y){
    AbstractEvent* event = new SpawnEvent(item->getUniqueId(), item->getId(), x, y);
    events.insert(std::make_pair(item->getUniqueId(), event));
}
void MapEvent::removeItem(Item* item){

    events.erase(item->getUniqueId());
}