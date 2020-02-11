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

        // Print out all connections that exist in the graph
        // This is only used for debugging
        void print();

        // Check whether this node was put into the graph (e.g. is connected to any other node.)
        bool node_exists(int node);
        bool node_exists(int node_x_coordinate, int node_y_coordinate);

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