#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>
#include "Items/OpenableItem.h"
#include "Items/Rocket.h"


class Item;
class Player;

class CellMap{
    bool occupied;
    std::vector<Item*> items;
    OpenableItem* door;
    std::vector<Player> playerList;
public:
    CellMap();
    //void transferPlayer(CellMap& otherCell);
    void removePlayer(Player& player);
    void addPlayer(Player& entity);
    bool hasPlayer();
    bool isSolid();
    void getItemsTile(Player& player,
                      std::vector<AbstractEvent*>& newEvents);
    bool hasItems();
    Item* removeItem();
    void addItem(Item* item);
    virtual void addItem(OpenableItem* item);
    void setSolid();
    void dropItems(Player& player);
    void dropItemPlayer(Item* item);
    bool isOpenable(Player& player, std::vector<AbstractEvent*>& newEvents);
    bool isOpen();
    virtual void incrementCooldown();
    bool impacts(Rocket* rocket, std::vector<AbstractEvent*>& newEvents);
    void explode(Rocket* rocket, std::vector<AbstractEvent *> &newEvents);


};


#endif //CELLMAP_H
