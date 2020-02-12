#ifndef HEX_H
#define HEX_H

#include<iostream>

#include "hexgraph.h"

using namespace std;

// This will simulate the board.
class Hex{
    public:
        // constructor
        Hex(int size, string player_blue, string player_red);

        // print method
        void print();

        // Check whether game is over
        bool game_over();
        bool player_red_won();
        bool player_blue_won();

        // Simulate a turn of a player.
        void player_red_turn();
        void player_blue_turn(); 

        
    private:
        // Size of the hex board
        int size;

        // Here the graphs for the two players are stored
        hexGraph PlayerRed;
        hexGraph PlayerBlue;

        // The choices of play
        string player_blue;
        string player_red;

        // Add nodes for users.
        bool add_node_red(int node_x, int node_y);
        bool add_node_blue(int node_x, int node_y);

};

#endif




