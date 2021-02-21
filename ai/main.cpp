#include <iostream>
#include <vector>

#include "AI.h"

int main() {
    ///////////////////////////
    std::vector<std::vector<int>> map;

    std::vector<int> row1;
    row1.push_back(1);
    row1.push_back(1);                      111
    row1.push_back(0);                      000
    map.push_back(row1);

    std::vector<int> row2;
    row2.push_back(0);
    row2.push_back(0);
    row2.push_back(0);
    map.push_back(row2);
    //////////////////////////
    std::vector<Player> players;
    players.emplace_back(16, 80, 0);// jugador id:  "0"
    players.emplace_back(48, 1, PI/2);// bot id:  "1"

    //////////////////////////
    int botId = 0;
    bool quit = false;

    AI ai(map, players, botId, quit);
    ai();
    return 0;
}
