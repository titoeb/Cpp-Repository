#ifndef HEX_H
#define HEX_H

#include<iostream>
#include<thread>
#include<limits>
#include<random>
#include<chrono>
#include<algorithm>

#include "hexgraph.h"

using namespace std;

const int N_THREADS = 8;
const int N_SIMULATIONS = 1500;

// Enum level for ai
enum class PlayerType{HUMAN, STUPIDAI};

// This will simulate the board.
class Hex{
    public:
        // constructor
        Hex(int size, PlayerType player_X, PlayerType player_O);

        // print method
        void print();

        // Check whether game is over
        bool game_over();
        bool O_won();
        bool X_won();

        // Take moves for players
        void player_O_turn();
        void player_X_turn();

    private:
        // Size of the hex board
        int size;

        // Here the graphs for the two players are stored
        hexGraph PlayerO; // Also known as player 0.
        hexGraph PlayerX; // Also known as player 1.

        // The choices of play
        PlayerType player_type_X;
        PlayerType player_type_O;

        // Simulate a turn of a player.
        void take_turn(hexGraph& player, PlayerType player_type, hexGraph& other_player);

        // Add nodes for users.
        bool add_node(hexGraph& this_player, hexGraph& other_player, int node_x, int node_y);

        // Get all actions that can still be done.
        vector<int> viable_moves();

        // Actions for the AI
        void user_move(hexGraph& player, hexGraph& other_player);
        void random_ai(hexGraph& player, hexGraph& other_player);
};

#endif




