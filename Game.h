//
//  Game.h
//  Proj3
//
//  Created by Tristan Ngo  on 5/30/23.
//
#include "Board.h"
#include "Side.h"
#include "Player.h"
#ifndef Game_h
#define Game_h
#include <string>
using namespace std;
class Game {
public:
    Game(const Board& b, Player* south, Player* north);
    void display() const;
    void status(bool &over, bool& hasWinner, Side& winner) const;
    bool move(Side s);
    void play();
    int beans(Side s, int hole) const;
private:
    Board bo;
    Player* pnorth;
    Player* psouth;
    Side s;
};








#endif /* Game_h */
