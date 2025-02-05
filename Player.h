
#include "Board.h"
#include "Side.h"
#ifndef Player_h
#define Player_h
#include <string>
using namespace std;

class Player {
    
public:
    Player(string name);
    string name() const;
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s ) const = 0;
    virtual ~Player();
private:
    string player_name;
};

class HumanPlayer : public Player {
public:
    HumanPlayer (string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~HumanPlayer();
};

class BadPlayer : public Player {
public:
    BadPlayer (string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~BadPlayer();
};

class SmartPlayer : public Player {
public:
    SmartPlayer (string name);
    //int help_move(const Board& b, Side s, int &hole, int & num);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~SmartPlayer();
private:
    int help_move(const Board& b, Side s, int& pickHole, int &num) const;
    int eval(const Board &b, Side s, int good_hole) const;
};







#endif /* Player_h */
