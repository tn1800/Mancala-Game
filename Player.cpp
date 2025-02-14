
#include "Player.h"
using namespace std;
#include <iostream>

Player :: Player (string name) : player_name(name) {
  
}

string Player :: name() const {
    return player_name;
}

bool Player :: isInteractive() const {
    return false;
}

Player :: ~ Player() {
    
}

HumanPlayer :: HumanPlayer (string name) : Player (name) {
    
}

bool HumanPlayer :: isInteractive() const {
    return true;
    
}

int HumanPlayer:: chooseMove(const Board& b, Side s) const {
    if (b.beansInPlay(s) == false) {
        return -1; //cant do the game if no beans are in play, return instantly.
    }
    int hole;
    cout << "Select a hole: ";
    cin >> hole;
    
    //if hole is invalid, try again, if fail again, keep trying until they enter valid hole.
    if (hole < 1 || hole > b.holes() || b.beans(s, hole) <= 0 ) {
        cout << "The hole entered is invalid, try again";
        cout << "Select a hole: " << endl;
        cin >> hole;
        while (hole < 1 || hole > b.holes() || b.beans(s, hole) <= 0 ) {
            cout << "The hole entered is invalid, try again";
            cout << "Select a hole: " << endl;
            cin >> hole;
        }
    }
    return hole;
}

HumanPlayer :: ~ HumanPlayer() {

}

BadPlayer :: BadPlayer (string name) : Player(name) {
    
}



int BadPlayer :: chooseMove(const Board& b, Side s) const {
    //checks south for first one with beans.
    if (s == SOUTH) {
        if (b.beansInPlay(SOUTH) == false) {
            return -1; //no valid move for south.
        }
        //south will return rightmost.
        for (int x = b.holes(); x > 0; x --) {
            if (b.beans(SOUTH, x) > 0) {
                return x;
            }
        }
    }//checks north for first one with beans.
    else if (s == NORTH) {
        if (b.beansInPlay(NORTH) == false) {
            return -1; //no valid move for south.
        }
        //north will return leftmost.
        for (int x = 1; x <= b.holes(); x ++) {
            if (b.beans(NORTH, x) > 0) {
                return x;
            }
        }
    } //if everything fails return -1;
return -1;
}

BadPlayer :: ~BadPlayer () {

}

SmartPlayer :: SmartPlayer (string name) : Player(name) {
    
}

int SmartPlayer :: chooseMove(const Board &b, Side s) const  {
   
    int chosen_hole = (b.holes()/2);
    int num = 0;
    chosen_hole = help_move(b, s, chosen_hole, num);
    return chosen_hole;
}


int SmartPlayer :: help_move (const Board& b, Side s, int& pickHole, int& num) const {
    int value = 0;
    Board copy = b;
    if (s == NORTH) {
        if (copy.beansInPlay(NORTH) <= 0) {
            pickHole = -1;
            value = 0;
            return value;
        }
    }
    int success_worth = 0;
    int max_success_worth = 0;
    int value_hole = 1; //evaluate each hole and after evaluating each hole return the hole with the highest value provided by eval.
    for (int x = 1; x <= b.holes(); x++) {
        if (copy.beans(s, x) > 0) {
            success_worth = eval(copy, s, x);
            if (success_worth > max_success_worth) {
                max_success_worth = success_worth;
                value_hole = x;
            }
        }
        
    }
    if (b.beans(s, value_hole) > 0) {
        return value_hole;
    } else {
        for (int x = 1; x <= b.holes(); x++) {
            if (copy.beans(s, x) > 0) {
                return x;
            }
        }
    }
    return -1;
}


int SmartPlayer :: eval(const Board &b, Side s, int good_hole) const {
    int value = 0;
    Board copy = b;
    Side end;
    int final_hole;
    Side opposite = SOUTH;
    int depth = 4;
    if (good_hole < 1 || good_hole > b.holes() || b.beans(s, good_hole) <= 0 ) {
        return -100000; //impossible move.
    }
    if (s == SOUTH) {
        opposite = NORTH;
    } else if (s == NORTH) {
        opposite = SOUTH;
    }
    
    if (copy.sow(s, good_hole, end, final_hole) == true) {
        if (copy.beans(end, final_hole) == 1 && b.beans(opposite, final_hole) > 0 ) {
            value = 50; //capture
            return value;
        }
        if (final_hole == 0 && end == s) {
            value = 10; //can take another turn.
        }
        if (final_hole == 1 && end == s) {
            value = 4; //close
        }
        if (final_hole == 2 && end == s && b.beans(s, final_hole) < 4) {
            value = 4; //close, easier to manipulate with less beans.
        }

        if (b.beansInPlay(s) <= 0 || b.beansInPlay(opposite) <= 0) {
            for (int x = 1; x <= b.holes(); x ++) {
                if (copy.beans(opposite, x) > 0) {
                    copy.moveToPot(opposite, x, opposite);
                }
                for (int x = 1; x <= b.holes(); x ++) {
                    if (copy.beans(s, x) > 0 ) {
                        copy.moveToPot(s, x, s);
                    }
                }
            }
            if (b.beans(s, 0) > b.beans(opposite, 0)) {
                return 10000;
            }
            if (b.beans(s, 0) < b.beans(opposite, 0)) {
                return -10000; //this is a bad move since it results in the opposite site ending up with more bea.s
            }
            if (b.beans(s, 0) == b.beans(opposite, 0)) {
                return 0; //tie is 0 value points.
            }
        } //this move results in winning, since theres no beans left on side, the rest of the beans go into opponent's pot, and if our side has more then its a good move.
            }
    if (depth > 0) {
        int b_o_value = 100000; // Opponent wants to minimize our score

        for (int x = 1; x <= b.holes(); x++) {
            if (copy.beans(opponent, x) > 0) {
                int opponent_eval = eval(copy, opponent, x, depth - 1);
                best_opponent_value = std::min(b_o_value, opponent_eval);
            }
        }

        value -= best_opponent_value; 
    }
    
    return value;
}

SmartPlayer :: ~SmartPlayer() {
    
}
