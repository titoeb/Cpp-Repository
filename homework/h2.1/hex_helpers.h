#ifndef HEX_HELPERS_H
#define HEX_HELPERS_H

#include<iostream>
#include<queue>
#include<ctime>
#include<cstdlib>
#include<deque>
#include<tuple>
#include<vector>
#include<algorithm>

using namespace std;
class Queue{
    public:

        // Constructor only allocates the internal queue nodes.
        Queue(int n_nodes):nodes(deque<int>()), is_in(vector<bool>(n_nodes, false)){}

        // Add a new node into the queue.
        // Think of a new node entering the closed set.
        void add(int node);

        // is_empty returns wether the queue is empty.
        // This is just for convenience
        bool is_empty();

        // Return the size of the queue
        int size();

        // Test wether node node is in the queue
        bool contains(int node);

        // Test whether any node in nodes is in the Queue.
        bool contains_any(vector<int> nodes);

        // Return the elements in an vector.
        vector<int> elements();

    private:
        int n_nodes;
        deque<int> nodes; 

        // This vector will be use to make fast is_in operation.
        vector<bool> is_in;
};


// Two data structures used for the smallest path algorithm
// A node will be tuple of int, float. to use the priority queue I need to define a custom comparison 
// To compare two points 
class GreaterNode{ 
public: 
    int operator() (const tuple<int, float>& node_1, const tuple<int, float>& node_2){ 
        return get<1>(node_1) > get<1>(node_2); 
    } 
}; 

// My implementation of a priority queue that will store nodes and there respective
// It will used for the open set later on.
class PriorityQueue{
    public:

        // Constructor only allocates the internal dequeue nodes and weigths
        PriorityQueue(int n_nodes):nodes(priority_queue <tuple<int, float>, vector<tuple<int, float>>, GreaterNode>()), is_in(vector<bool>(n_nodes, false)){}

        // Add a new node into the Priority qeue.
        // Find the correct position and insert it in both
        // the nodes deqeue and the weight deqeue.
        void add(int node, float weight);

        // Give the first nodes and its weight and remove it from the priority queue
        tuple<int, float> pop();
        
        // Return the size of the queue
        int size();

        // Print the priority queue.
        void print();

        // is_empty returns wether the priority queue is empty.
        // This is just for convenience
        bool is_empty();

        // Test wether node node is in the queue
        bool contains(int node);

    private:
        priority_queue <tuple<int, float>, vector<tuple<int, float>>, GreaterNode> nodes; 
        vector<bool> is_in;
};

// Short logic to convert map to coordinate and vice versa
int coordinate2node(int x_coordinate, int y_coordinate, int dimensions_board);
int node2coordinate_x(int node, int dimensions_board);
int node2coordinate_y(int node, int dimensions_board);

// check whether a node is in the board
bool is_in(int x_coordinate, int y_coordinate, int dimensions_board);

// check whether an integer is neither in dquee a or b.
bool not_in_deques(int node,  deque<int> deque1, deque<int> deque2);

// Random integer between min and max
int rand_int(int begin, int end);

// Find position of maximum within a float vector
int argmax(vector<float> values);

#endif




