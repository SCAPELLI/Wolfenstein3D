#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>
#include "server/Items/OpenableItem.h"
#include "server/Items/Rocket.h"

/* Clase que representa una posición en el mapa y contiene los elementos en esa posición*/
class Item;
class Player;
class GameLoader;

class CellMap{
    bool occupied;
    std::vector<Item*> items;
    OpenableItem* door;
    std::vector<Player> playerList;
public:
    CellMap();
    void removePlayer(Player& player);
    void addPlayer(Player& entity);
    bool isSolid();
    void getItemsTile(Player& player,
                      std::vector<AbstractEvent*>& newEvents);
    OpenableItem* getDoor();
    void addItem(Item* item);
    virtual void addItem(OpenableItem* item);
    void setSolid();
    void dropItems(Player& player,GameLoader& factory,
                            std::vector<AbstractEvent*>& newEvents);
    bool isOpenable(Player& player, std::vector<AbstractEvent*>& newEvents);
    bool isOpen();
    virtual void incrementCooldown();
    bool impacts(Rocket* rocket, std::vector<int>& damagedPlayers);
    void explode(Rocket* rocket, std::vector<int>& damagedPlayers);
    bool isLockedDoor();

};


#endif //CELLMAP_H
