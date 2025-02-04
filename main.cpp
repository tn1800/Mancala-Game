
//  main.cpp
//  Proj3
//
//  Created by Tristan Ngo  on 5/21/23.
//
#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "Side.h"
using namespace std;
#include <iostream>

int main(int argc, const char * argv[]) {
  
//    cout << "HI" << endl;
    Board b(6, 3);
    BadPlayer bad("Bob");
    HumanPlayer hp("Tristan");
    Game g(b, &hp, &bad);
    g.play();
    return 0; 
    
//            BadPlayer bp1("Bart");
//            BadPlayer bp2("Homer");
//            Board b(3, 0);
//            b.setBeans(SOUTH, 1, 2);
//            b.setBeans(NORTH, 2, 1);
//            b.setBeans(NORTH, 3, 2);
//            Game g(b, &bp1, &bp2);
//            bool over;
//            bool hasWinner;
//            Side winner;
//              //    Homer
//              //   0  1  2
//              // 0         0
//              //   2  0  0
//              //    Bart
//            g.status(over, hasWinner, winner);
//            assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
//            g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
//            g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//
//            g.move(SOUTH);
//              //   0  1  0
//              // 0         3
//              //   0  1  0
//            g.status(over, hasWinner, winner);
//    assert(!over);
//    assert(g.beans(NORTH, POT) == 0);
//    assert(g.beans(SOUTH, POT) == 3);
//
//            assert(g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
//            g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//            g.move(NORTH);
//              //   1  0  0
//              // 0         3
//              //   0  1  0
//            g.status(over, hasWinner, winner);
//            assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//            g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//            g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//            g.move(SOUTH);
//              //   1  0  0
//              // 0         3
//              //   0  0  1
//            g.status(over, hasWinner, winner);
//            assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//            g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//            g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
//
//            g.move(NORTH);
//              //   0  0  0
//              // 1         4
//              //   0  0  0
//            g.status(over, hasWinner, winner);
//            assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
//            g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//            g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//            assert(hasWinner && winner == SOUTH);

//    HumanPlayer hp("Marge");
//            assert(hp.name() == "Marge"  &&  hp.isInteractive());
//            BadPlayer bp("Homer");
//            assert(bp.name() == "Homer"  &&  !bp.isInteractive());
//            SmartPlayer sp("Lisa");
//            assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
//            Board b(3, 2);
//            b.setBeans(SOUTH, 2, 0);
//            cout << "=========" << endl;
//            int n = hp.chooseMove(b, SOUTH);
//            cout << "=========" << endl;
//            assert(n == 1  ||  n == 3);
//            n = bp.chooseMove(b, SOUTH);
//            assert(n == 1  ||  n == 3);
//            n = sp.chooseMove(b, SOUTH);
//            assert(n == 1  ||  n == 3);
}
//
