#ifndef HEXGRAPH_H
#define HEXGRAPH_H

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

#include "hex_helpers.h"

using namespace std;

// Function interacting with the user and steering the game.

class hexGraph{
    public:
        // Construct hex graph of appropriate size
        hexGraph(int dimension);

        // Add a single node into the graph.
        void addNode(int x, int y);
        void addNode(int node);

        // Print out all connections that exist in the graph
        // This is only used for debugging
        void print();

        // Check whether this node was put into the graph (e.g. is connected to any other node.)
        bool node_exists(int node);
        bool node_exists(int node_x_coordinate, int node_y_coordinate);

        // Test whether two nodes are connected.
        bool is_connected(int node_a, int node_b);
        bool is_connected(int node_a_x_coordinate, int node_a_y_coordinate, int node_b_x_coordinate, int node_b_y_coordinate);

        // Test whether one of the upper nodes is connect to one of the lower nodes or one of 
        // the left node is connected to one of the right nodes.
        bool sides_connected();

        // Check if any of the nodes in connected is connected to the nodes in connected_to
        bool nodes_connected(vector<int> connected, vector<int> connected_to);

    private:
        int dimension;
        vector<deque<int> > edgelist;
}; 

#endif