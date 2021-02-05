#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>
#include "Items/OpenableItem.h"
#include "MapEvent.h"
//#include "../server/GameLoader.h"
//#include "GameLoader.h"

class Item;
class Player;
class GameLoader;

class CellMap{
    bool occupied;
    std::vector<Item*> items;
    OpenableItem* door;
    std::vector<Player> playerList;
    //GameLoader yamli;
public:
    CellMap();
    //void transferPlayer(CellMap& otherCell);
    void removePlayer(Player& player);
    void addPlayer(Player& entity);
    bool hasPlayer();
    bool isSolid();
    void getItemsTile(Player& player, MapEvent& changes);
    bool hasItems();
    Item* removeItem();
    void addItem(Item* item);
    virtual void addItem(OpenableItem* item);
    void setSolid();
    void dropItems(Player& player);
    void dropItemPlayer(Item* item);
    bool isOpenable(Player& player);
    bool isOpen();
    virtual void incrementCooldown();


};


#endif //CELLMAP_H
