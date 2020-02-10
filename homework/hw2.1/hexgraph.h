#ifndef HEXGRAPH_H
#define HEXGRAPH_H

#include<iostream>
#include<queue>

#include "hex_helpers.h"

using namespace std;

// Function interacting with the user and steering the game.

class hexGraph{
    public:
        // Construct hex graph of appropriate size
        hexGraph(int dimension);

        // Add a single node into the graph.
        void addNode(int x, int y);
            
        // Test whether two nodes are connected.
        bool is_connected(int node_a, int node_b);
        bool is_connected(int node_a_x_coordinate, int node_a_y_coordinate, int node_b_x_coordinate, int node_b_y_coordinate);

        // Find the longest path in the graph.
        // To Do

    private:
        int dimension;
        vector<deque<int> > edgelist;
};

#endif