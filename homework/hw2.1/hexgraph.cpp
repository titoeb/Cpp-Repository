#include "hexgraph.h"

hexGraph::hexGraph(int dimension):dimension(dimension){
    
    int count_nodes = 0;
    this->edgelist.resize(this->dimension * this->dimension);

    // Allocate the nodes:
    // X-coordinate:
    for(int x; x < this->dimension; ++x){
        // Y-coordinate:
        for(int y; y < this->dimension; ++y){
            // Determine the kind of node
            hexGraph::addNode(x, y, this->edgelist[coordinate2node(x, y, this->dimension)]);
        }
    }
}

void hexGraph::addNode(int x, int y, deque<int> queue){
    // Try to add all surroundings of the node, if they exist.
    // Row above:
        // Add node (x-1, y-1)
        if (is_in(x-1, y-1, this->dimension)){
            queue.push_front(coordinate2node(x - 1, y - 1, this->dimension));
        }  

        // Add node (x-1, y)  
        if (is_in(x-1, y, this->dimension)){
            queue.push_front(coordinate2node(x - 1, y, this->dimension));
        }    

        // Add node (x-1, y+1)
        if (is_in(x-1, y+1, this->dimension)){
            queue.push_front(coordinate2node(x - 1, y + 1, this->dimension));
        }  

    // Same row:
        // Add node (x, y-1)
        if (is_in(x, y-1, this->dimension)){
            queue.push_front(coordinate2node(x, y - 1, this->dimension));
        }  

        // Add node(x, y+1)
            if (is_in(x, y+1, this->dimension)){
            queue.push_front(coordinate2node(x, y + 1, this->dimension));
        }  

    // Row below:

        // Add node (x+1, y-1)
            if (is_in(x+1, y-1, this->dimension)){
            queue.push_front(coordinate2node(x + 1, y - 1, this->dimension));
        }  

        // Add node (x+1, y)
            if (is_in(x+1, y, this->dimension)){
            queue.push_front(coordinate2node(x + 1, y - 1, this->dimension));
        }  

        // Add node (x+1, y+1)
            if (is_in(x+1, y+1, this->dimension)){
            queue.push_front(coordinate2node(x, y + 1, this->dimension));
        }  
}
