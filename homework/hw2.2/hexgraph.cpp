#include "hexgraph.h"

// Implementations of functions for hexGraph:
// Constructor for class hexGraph
hexGraph::hexGraph(int dimension):dimension(dimension){
    this->edgelist.resize(this->dimension * this->dimension);
}
// Add a node to the graph
void hexGraph::addNode(int x, int y){
    // Try to add all surroundings of the node, if they exist.
    int this_node = coordinate2node(x, y, this->dimension);
    // Row above:
        // Add node (x-1, y)  
        if (is_in(x-1, y, this->dimension)){
            this->edgelist[this_node].push_front(coordinate2node(x - 1, y, this->dimension));
        }    

        // Add node (x-1, y+1)
        if (is_in(x-1, y+1, this->dimension)){
            this->edgelist[this_node].push_front(coordinate2node(x - 1, y + 1, this->dimension));
        }  

    // Same row:
        // Add node (x, y-1)
        if (is_in(x, y-1, this->dimension)){
            this->edgelist[this_node].push_front(coordinate2node(x, y - 1, this->dimension));
        }  

        // Add node(x, y+1)
        if (is_in(x, y+1, this->dimension)){
            this->edgelist[this_node].push_front(coordinate2node(x, y + 1, this->dimension));
        }  

    // Row below:
        // Add node (x+1, y-1)
            if (is_in(x+1, y-1, this->dimension)){
            this->edgelist[this_node].push_front(coordinate2node(x + 1, y - 1, this->dimension));
        }  

        // Add node (x+1, y)
            if (is_in(x+1, y, this->dimension)){
            this->edgelist[this_node].push_front(coordinate2node(x + 1, y, this->dimension));
        }
}

// Check whether this node was put into the graph (e.g. is connected to any other node.)
bool hexGraph::node_exists(int node){
    return (this->edgelist[node].size() > 0);
}
bool hexGraph::node_exists(int node_x_coordinate, int node_y_coordinate){
    return node_exists(coordinate2node(node_x_coordinate, node_y_coordinate, this->dimension));
}

// Print out all nodes that exist
void hexGraph::print(){
    for(int node=0; node < this->edgelist.size(); ++node){
        if(this->edgelist[node].size() > 0){
            for(int i = 0; i < this->edgelist[node].size(); ++i){
                cout << "Node (" << node2coordinate_x(node, this->dimension) << "," <<node2coordinate_y(node, this->dimension) << ")" << " is connected to (" << node2coordinate_x(this->edgelist[node][i], this->dimension) << "," << node2coordinate_y(this->edgelist[node][i], this->dimension) << ")" << "." << endl;
            }
        }
    }
}

// Test whether two nodes are connected.
// Test whether two nodes are connected.

// This is the main function, the version below just uses this one.
bool hexGraph::is_connected(int node_a, int node_b){
    if (node_a == node_b){
        return true;
    }

    deque<int> open_set, closed_set;
    int current_node;
    
    // Initiallize: Put node_a into closed set, all its neighboors into the open set 
    closed_set.push_front(node_a);
    for(int i = 0; i < this->edgelist[node_a].size(); ++i){
        open_set.push_front(this->edgelist[node_a][i]);
    }      

    // Iterate: While open_set not empty:
        // Select node and put it into closed set, put all its neighboors that are neither in the open nor the closed set into the open set.
    while(open_set.size() > 0){
        // Get the last element from the queue
        current_node = open_set.back();

        // Remove the last element from the queue
        open_set.pop_back();

        // Put the node into the closed set, if the node is node_b return true
        if (current_node == node_b){
            return true;
        } else {
            closed_set.push_front(current_node);

            // Put all nodes that are adjecent to node b into the open set, if they are neither in the open nor close set.
            for(int i = 0; i < this->edgelist[current_node].size(); ++i){
                if(not_in_deques(this->edgelist[current_node][i], open_set, closed_set)){
                    open_set.push_front(this->edgelist[current_node][i]);
                }    
            }    
        }
    }
    // If we did not put node_b at some point into the closed set, it is not connected to a.
    return false;
}

// This will simply execute the function above.
bool hexGraph::is_connected(int node_a_x_coordinate, int node_a_y_coordinate, int node_b_x_coordinate, int node_b_y_coordinate){
    return is_connected(coordinate2node(node_a_x_coordinate, node_a_y_coordinate, this->dimension), coordinate2node(node_b_x_coordinate, node_b_y_coordinate, this->dimension));
}

// Test whether one of the upper nodes is connect to one of the lower nodes or one of 
// the left node is connected to one of the right nodes.
bool hexGraph::sides_connected(){
    // Check if the upper side is connected to the lower side.
    vector<int> upper_side(this->dimension);
    vector<int> lower_side(this->dimension);
    
    for(int i=0; i < this->dimension; ++i){
        upper_side.push_back(coordinate2node(0, i, this->dimension));
        lower_side.push_back(coordinate2node(this->dimension - 1, i, this->dimension));
    }

    if (this->nodes_connected(upper_side, lower_side) == true){
        return true;
    }

    // Check if the left side is connected to the right side.
    // Check if the upper side is connected to the lower side.
    vector<int> left_side(this->dimension);
    vector<int> right_side(this->dimension);
    
    for(int i=0; i < this->dimension; ++i){
        left_side.push_back(coordinate2node(i, 0, this->dimension));
        right_side.push_back(coordinate2node(i, this->dimension - 1, this->dimension));
    }

    if (this->nodes_connected(left_side, right_side) == true){
        return true;
    }

    // If we did not find any matches, the sides are not connected
    return false;
}

// Test whether one of the upper nodes is connect to one of the lower nodes or one of 
// the left node is connected to one of the right nodes.
bool hexGraph::nodes_connected(vector<int> connected, vector<int> connected_to){
    // Check whether the nodes stores in connected are connect to the nodes in 

        // Allocate open and closed set.
    deque<int> open_set(this->dimension);
    Queue closed_set(this->dimension);
    
    // tuple to hold the poped entries from the open set
    int next_node;

    // Used to temporary store the node just retrieved from the open set.
    int node;

    // Store the neigbors of the node.
    vector<int> neighbors;

    // Begin with algorithm.
    // Add all starting nodes to the open set.
    for(auto node: connected){
        open_set.push_front(node);
    }
    
    // Iterate until either the open set is empty or the 
    while((!open_set.empty()) && (!closed_set.contains_any(connected_to))){
        
        // Get the minimal node from the open set.
        next_node = open_set.front();
        open_set.pop_front();

        // Check whether this node is already in the closed because duplicates can be in the open set!
        if(closed_set.contains(node)){

            // If the node is already in the closed set we don't need to consider it
                continue;
        }

        for(auto nb: this->edgelist[next_node]){
            // Only put a node into the open set, if it is not already in the closed set
            if(!closed_set.contains(nb)){
                // Depending on whether the node is already in the open set, we either have to update its weight, or to inser it.
                open_set.push_front(nb);
            }
        }
    }

    if (closed_set.contains_any(connected_to)){
        // We found the path between the sets of nodes
        return true;

    } else {

        // There is no path between the set of nodes.
        return false;
    }
}
    