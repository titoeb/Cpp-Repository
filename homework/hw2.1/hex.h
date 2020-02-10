#ifndef HEX_H
#define HEX_H

#include<iostream>

#include "hexgraph.h"

using namespace std;

// This will simulate the board.
class Hex{
    public:
        // constructor
        Hex(int size);

        // print method
        void print();



    private:
        // Size of the hex board
        int size;
        hexGraph Player1;
        hexGraph Player2;
};

#endif




