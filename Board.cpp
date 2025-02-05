

#include "Board.h"
#include <vector>
using namespace std;
Board :: Board(int nHoles, int nInitialBeansPerHole) {
    if (nHoles <= 0) {
        qHoles = 1;
    }
    else {
        qHoles = nHoles;
    }
    if (nInitialBeansPerHole < 0) {
        nInitialBeansPerHole = 0;
    }
    n.push_back(0);
    so.push_back(0);
    for (int x = 0; x < qHoles; x ++) {
        n.push_back(nInitialBeansPerHole);
        so.push_back(nInitialBeansPerHole);
    }
}

int Board :: holes () const {
    return qHoles;
}

int Board ::  beans(Side s, int hole) const {
    if (hole > n.size()) {
        return -1;
    }
    if (s == SOUTH)
        if(hole <= qHoles)
    {
        return so[hole];
    }
    if (s == NORTH && hole <= qHoles) {
        return n[hole];
    }
    return -1;
}

int Board :: beansInPlay(Side s) const {
    int southCounter = 0;
    int northCounter = 0;
    if (s == SOUTH) {
        for (int x = 1; x < so.size(); x ++) {
            southCounter = southCounter + so[x];
        }
        return southCounter;
    }
    if (s == NORTH) {
        for (int x = 1; x < n.size(); x ++) {
            northCounter = northCounter + n[x];
        }
        return northCounter;
    }
    return -1;
    
}

int Board :: totalBeans() const {
    int total = 0;
    for (int x = 0; x < so.size(); x ++) {
        total = total + so[x];
    }
    for (int x = 0; x < n.size(); x ++) {
        total = total + n[x];
    }
    
    return total;
    
}

bool Board :: sow(Side s, int hole, Side& endSide, int& endHole) {
    //hole has to exist and cant be the pot.
    int tempSide = s;
    if (hole <= 0 || hole > qHoles) {
        return false;
    }
    //cant be invalid side
    if (s != NORTH && s != SOUTH)  {
        return false;
    } //have to have beans to sow.
    if (beans(s, hole) <= 0) {
        return false;
    }
    
    if (tempSide == NORTH) {
        int north_amount;
        int south_amount;
        if (n[hole] > 0) {
           
            north_amount = n[hole];
           // cout << "did we get here" << north_amount << endl;
        } else {
            return false;
        }
        n[hole] = 0; //hole has 0 now, since its about to sow.
        
        int currentHole = (hole - 1);
       // cerr << "current hole is " << currentHole << endl;
        while(north_amount > 0) {
            for (int x = currentHole; north_amount > 0 && x >= 0; x--) {
                north_amount = north_amount - 1;
                n[x] = n[x] + 1;
            //    cerr << "inside" << x << "there is " << n[x] << endl;
                if (north_amount <= 0) {
                    endHole = x;
                    endSide = NORTH;
                    return true;
                }
              
            }
           // if we looped through north, but still have beans left, we go to south.
            int starting_south = 1;
            south_amount = north_amount;  //gets the amount of beans left still to sow.
            for (int x = starting_south; x < so.size() && south_amount > 0; x ++) {
                so[x] = so[x] + 1;
                north_amount = north_amount - 1;
                if (north_amount <= 0) {
                    endHole = x;
                    endSide = SOUTH;
                    return true;
                }
            }
            currentHole = so.size() - 1; //if we loop through south have to get back to north and can start at its last hole.
        }
        
    }
    if (s == SOUTH) {
        
        if (so[hole] <= 0) {
            return false;
        }
        tempSide = SOUTH;
        int south_hole = so.size();
      //  cerr << "size is " << south_hole << endl;
        int south_amount = so[hole];
//        cerr << "hole is " << hole << endl;
//        cerr << "inside hole 1 is " << so[1] << endl;
//        cerr << "south amount is " << south_amount << endl;
        so[hole] = 0;
        int begin_hole = hole + 1;
        int hole_tracker = hole;
        
    //   cerr << "southamoutn is " << south_amount << endl;
    //    cerr << "hole begining is " << begin_hole << endl;
//        cout << "we are begining at " << begin_hole << endl;
//        cout << "south_amount is" << south_amount << endl;
        while (south_amount > 0) {
            for (int x = begin_hole; x < south_hole && south_amount != 0; x++) {
             //   cerr << "Does loop" << endl;
                if (south_amount != 0) {
                    
                    south_amount = south_amount - 1;
                    so[x] = so[x] + 1;
//                    cout << "hole" << x << "has" << so[x] << endl;
                    hole_tracker++;
//                    cout << "HII" << endl;
                }
                //no more beans to sow, so at the final hole.
                if (south_amount == 0) {
//                    cout << "endHole is " << x;
                    
                    endHole = x;
                    endSide = SOUTH;
                    return true;
                    
                }
            } //reached south's pot on the far right.
//            cout << "we are before holetracker, amount is" << south_amount << endl;
            hole_tracker++;
            if (tempSide == SOUTH && hole_tracker >= so.size() && south_amount > 0) {
//                cout << "arrive at south hole" << endl;
//                cout << "south amount is" << south_amount << endl;
                so[0] = so[0] + 1;
                south_amount = south_amount - 1;
//                cerr << "lol" << endl;
                if (south_amount == 0) {
                    endSide = SOUTH;
                    endHole = 0;
                    return true;
                }
            }
//            cout << "after leaving south amount is" << south_amount << endl;
            //continue to north side if there are still beans left.
            int north_amount = n.size() - 1;
         //   cerr << "before enteirng n" << south_amount << endl;
            if (south_amount > 0) {
                for (int s = north_amount; s > 0; s --) {
//                    cout << "entering north, north amount is" << north_amount << endl;
//                    cout << "s is" << s << endl;
                    south_amount = south_amount - 1;
//                    cout << "south amount is" << south_amount << endl;
                    n[s] = n[s] + 1;
               //     cerr << "south_amoutn is now" << south_amount << endl;
//                    if (south_amount != 0) {
//                        north_amount++;
//                    }
                    if (south_amount == 0) {
                        endSide = NORTH;
                        endHole = s;
                        // cout << "3 is" << so[3] << endl;
                        return true;
                    }
                 //   cout << "south amount is" << south_amount << endl;
                    
                }
            }
            begin_hole = 1; //must reset it to one so when we go back to south we start at 1.
            
        }
        
    }
        
        if (s == SOUTH || s == NORTH) {
        return true;
    }
    else
        return false;
}

bool Board:: moveToPot(Side s, int hole, Side potOwner) {
//    cout << "HOLE IS" << hole << endl;
    if (hole > qHoles || hole <= 0) {
//        cout << "u " << endl;
        return false;
    } //if hole is not valid or a pot, return false.
    
    if(s == SOUTH) {
//        cout << "SOUTH HERE" << endl;
        int beans = so[hole];
        so[hole] = 0;
        if (potOwner == NORTH) {
            n[0] = n[0] + beans;
        }
        if (potOwner == SOUTH) {
            so[0] = so[0] + beans;
        }
    }
    if (s == NORTH) {
//        cout << "NORTH HERE" << endl;
        int bean_north = n[hole];
        n[hole] = 0;
        if (potOwner == NORTH) {
            n[0] = n[0] + bean_north;
        }
        if (potOwner == SOUTH) {
            so[0] = so[0] + bean_north;
        }
        }
    return true;
}


bool Board :: setBeans(Side s, int hole, int beans) {
    //returns false if not hole or pot valid.
    if (hole < 0 || hole > qHoles) {
        return false;
    }
    if (s == NORTH) {
        n[hole] = beans;
    }
    else if (s == SOUTH) {
        so[hole] = beans;
    }
    if (s != SOUTH && s != NORTH) {
        return false; //invalid side.
    }
    return true;
    
}
