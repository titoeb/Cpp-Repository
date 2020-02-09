#ifndef HEX_H
#define HEX_H

#include<iostream>
using namespace std;

// Function interacting with the user and steering the game.
enum class Player{P1, P2, Empty};

// This will simulate the board.
class Board{
    public:
        // constructor
        Board(int size);

        // print method
        void print();

        // Getter and setter
        Player get_position(int row, int col);

        void set_position(int row, int col, Player p);

    private:
        // Size of the hex board
        int size;
};

#endif




