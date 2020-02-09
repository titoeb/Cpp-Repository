#ifndef HEXGRAPH_H
#define HEXGRAPH_H

#include<iostream>
#include<vector>
#include<queue>

#include "hex_helpers.h"

using namespace std;

// Function interacting with the user and steering the game.

class hexGraph{
    public:
        // Construct hex graph of appropriate size
        hexGraph(int dimension);

        // Add a single node into the graph.
        void addNode(int x, int y, deque<int> queue);

    private:
        int dimension;
        vector<deque<int> > edgelist;
};

#endif