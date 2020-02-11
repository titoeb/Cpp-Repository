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

        // Check whether game is over
        bool game_over();
        bool player_red_won();
        bool player_blue_won();

        // Add nodes for users
        bool add_node_red(int node_x, int node_y);
        bool add_node_blue(int node_x, int node_y);

    private:
        // Size of the hex board
        int size;
        hexGraph PlayerRed;
        hexGraph PlayerBlue;
};

#endif




