
#include "Game.h"
using namespace std;
#include <iostream>

Game :: Game(const Board& b, Player* south, Player* north) : bo(b) {
    pnorth = north;
    psouth = south;
    s = SOUTH;
}

void Game :: display() const {
    cout << "   " + pnorth -> name() << endl;
    //print space if there are holes for north
    if (bo.holes() > 0) {
        cout << "   ";
    }
    //prints out the north holes, then afterwards has creates new line to print out the pot.
    for (int x = 1; x <= bo.holes(); x ++) {
        cout << bo.beans(NORTH, x) << " ";
    }
    cout << endl << "  ";
    cout << bo.beans(NORTH, 0);
    int x = 1;
    while (x <= bo.holes()) {
        cout << "  ";
        x++;
    }
   //prints south's pot whihc is on same line as north's pot.
   
    cout << bo.beans(SOUTH, 0) << endl;
    cout << "   ";
    for (int x = 1; x <= bo.holes(); x++) {
        cout << bo.beans(SOUTH, x) << " ";
    }
    cout << endl;
    cout << "  " << " " << psouth -> name() << endl;
}
void Game :: status(bool& over, bool & hasWinner, Side& winner) const {
    if (bo.beansInPlay(NORTH) > 0 && bo.beansInPlay(SOUTH) > 0) {
        over = false;
        return;
    }
    if (bo.beansInPlay(NORTH) <= 0 || bo.beansInPlay(SOUTH) <= 0) {
        over = true;
        
    }
    int n = NORTH;
    int s = SOUTH;
    //draw if beans inside the pots are the same.
    if (bo.beans(NORTH, 0) == bo.beans(SOUTH, 0)) {
        hasWinner = false;
    }
    int pot_north = bo.beans(NORTH, 0);
    int pot_so = bo.beans(SOUTH, 0); //if north pot has more than southpot beans then north wins vice versa
    if (pot_north > pot_so) {
        hasWinner = true;
        winner = NORTH;
    }
    else if (bo.beans(SOUTH, 0) > bo.beans(NORTH, 0)) {
        hasWinner = true;
        winner = SOUTH;
    }
    else {
        hasWinner = false;
    }
    return;
}
bool Game :: move(Side s) {
    bool finished = false;
    bool win = false;
    Side temp = s;
    int final_hole;
    Side north_south;
    string winner;
     if (s == NORTH) {
    int nHuman = pnorth -> isInteractive();
    int north_pick = pnorth -> chooseMove(bo, NORTH);
    cout << "north chooses hole number " << north_pick << endl;
    int north_final, end_final = 0;
    Side tempo = NORTH;
        // int hole = psouth -> chooseMove(bo, NORTH);
        if (bo.sow(NORTH, north_pick, tempo, north_final)) {
           // cout << "did we get int osowing" << endl;
            if (tempo != SOUTH && north_final == 0) { //make sure we are in our pot in the north {
                display();
                if (bo.beansInPlay(NORTH) > 0) {
                    cout << pnorth -> name() << " goes again." << endl;
                    return move(NORTH);
//                    if (s == NORTH) {
//                        return move(SOUTH);
//                    }
                }
            } else if (tempo == NORTH && bo.beans(s, north_final) == 1 && bo.beans(SOUTH, north_final) > 0) { //we can do a capture if we're on our side and we have exactly 1 bean in our specific hole since that means we just got there.
                bo.moveToPot(SOUTH, north_final, NORTH);
                bo.moveToPot(NORTH, north_final, NORTH);
//                if (bo.beansInPlay(NORTH) > 0) {
//                    return (NORTH);
//                }
            }
        }
    } else if (s == SOUTH) {
        int pick = 0;
        bool robot = psouth -> isInteractive();
        pick = psouth -> chooseMove(bo, SOUTH);
        cout << "South chooses hole number " << pick << endl;
        string south_name = psouth -> name();
        bool canSow = bo.sow(SOUTH, pick, north_south, final_hole);
        if (canSow == true && north_south < 2) {
            string south_name = psouth -> name();
            if (final_hole == 0) {
                display();
                if (bo.beansInPlay(SOUTH) > 0) {
                  //  cout << south_name << "will go again" << endl;
                    return move(SOUTH); //recursion take another turn, pass in the south side since south gets another turn.
                }
            }
            else if (bo.beans(s, final_hole) == 1 && bo.beans(NORTH, final_hole) > 0 && north_south == SOUTH) {
                bo.moveToPot(NORTH, final_hole, SOUTH); //make sure that there are beans that can be captured on opposite side, and if our beans are 1 in that hole, then we just arrived in it.
                bo.moveToPot(SOUTH, final_hole, SOUTH);
            }
        }
        else {
            north_south = NORTH;
        }
    }
    if (bo.beansInPlay(SOUTH) <= 0 || bo.beansInPlay(NORTH) <= 0) {
        display(); //if one side has beans left but the other dosent sweep beans on the side with not many into their pot.
        winner = (bo.beans(NORTH, 0) > bo.beans(SOUTH, 0)) ? pnorth->name() : psouth -> name();
        cout << "The beans on " + winner  << "'s side will now be swept into their pot. There are no more beans in play anymore." << endl;
        for (int x = 1; x <= bo.holes(); x ++) {
            bo.moveToPot(SOUTH, x, SOUTH);
            bo.moveToPot(NORTH, x, NORTH);
        }
        return false;
        
    }
    return true;
}
 
    
void Game :: play() {
    Side vwinner = SOUTH;
    bool finished = false;
    bool win = false;
    bool over, hasWinner;
    Side winner;
    display();
    Side s = SOUTH;
    move(s);
    display();
    bool robot_south = psouth->isInteractive();
    bool robot_north = pnorth->isInteractive();
    bool both = (robot_north == false && robot_south == false);
    if (robot_north == false && robot_south == false) {
        cout << "Press enter to continue";
        cin.ignore(10000, '\n');
    }
    status(finished, win, winner);
    s = NORTH;
    while (finished == false) {
        move(s); //keep the game going until its finished, by making moves and switching the input into the move function so each side takes turn making moves.
        display();
        if (both == true) {
            cout << "Press enter to continue";
            cin.ignore(10000, '\n');
        }
        status(finished, win, winner);
        if (s == NORTH) { //have to switch players for the move input.
            s = SOUTH;
        } else if (s == SOUTH) {
            s = NORTH;
        }
    }
    if (win == true) {
        if (winner == NORTH) {
            cout << "The winner of the game is " << pnorth -> name() << endl;
        }
        if (winner == SOUTH) {
            cout << "The winner of the game is " << psouth -> name() << endl;
        }
    }
    if (win == false) {
        cout << "There is no winner. The result is a tie." << endl;
    }
    
  
}
    
int Game :: beans(Side s, int hole) const {
    if (hole > bo.holes() || hole < 0) {
        return -1;
    }
    else {
        return bo.beans(s, hole);
    }
}
    
    
