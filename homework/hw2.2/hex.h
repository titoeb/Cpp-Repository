#ifndef HEX_H
#define HEX_H

#include<iostream>

#include "hexgraph.h"

using namespace std;

// Enum level for ai
enum class Player{HUMAN, STUPIDAI, SMARTAI};

// This will simulate the board.
class Hex{
    public:
        // constructor
        Hex(int size, Player player_blue, Player player_red);

        // print method
        void print();

        // Check whether game is over
        bool game_over();
        bool red_won();
        bool blue_won();

        // Simulate a turn of a player.
        void player_red_turn();
        void player_blue_turn(); 

        // Actions for the AI
        void user_move(int player);
        void random_ai(int player);

        
    private:
        // Size of the hex board
        int size;

        // Here the graphs for the two players are stored
        hexGraph PlayerRed; // Also known as player 0.
        hexGraph PlayerBlue; // Also known as player 1.

        // The choices of play
        Player player_blue;
        Player player_red;

        // Add nodes for users.
        bool add_node_red(int node_x, int node_y);
        bool add_node_blue(int node_x, int node_y);

};

#endif




