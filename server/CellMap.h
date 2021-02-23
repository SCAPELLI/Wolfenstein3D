#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>
#include "Items/OpenableItem.h"
#include "Items/Rocket.h"

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
    bool hasPlayer();
    bool isSolid();
    void getItemsTile(Player& player,
                      std::vector<AbstractEvent*>& newEvents);
    void addItem(Item* item);
    virtual void addItem(OpenableItem* item);
    void setSolid();
    void dropItems(Player& player,GameLoader& factory,
                            std::vector<AbstractEvent*>& newEvents);
    void dropItemPlayer(Item* item);
    bool isOpenable(Player& player, std::vector<AbstractEvent*>& newEvents);
    bool isOpen();
    virtual void incrementCooldown();
    bool impacts(Rocket* rocket, std::vector<AbstractEvent*>& newEvents);
    void explode(Rocket* rocket, std::vector<AbstractEvent *> &newEvents);


};


#endif //CELLMAP_H
