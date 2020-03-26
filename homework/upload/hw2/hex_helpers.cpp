#include "hex_helpers.h"

// Implementation for the Queue

// Add a new node into the queue.
// Think of a new node entering the closed set.
void Queue::add(int node){
    this->nodes.push_front(node);
    this->is_in[node] = true;
}

// is_empty returns wether the queue is empty.
// This is just for convenience
bool Queue::is_empty(){
    return this->size() == 0;
}

// Return the size of the queue
int Queue::size(){
    return this->nodes.size();
}

// Test wether node node is in the queue
bool Queue::contains(int node){
    return this->is_in[node];
}

// Test whether any node in nodes is in the Queue.
bool Queue::contains_any(vector<int> nodes){
    for(auto node: nodes){
        if(this->contains(node)){

            return true;
        }
    }
    return false;
}

// Return the elements in an vector.
vector<int> Queue::elements(){

    // Initiallize to the accordings size
    vector<int> elements(this->size());

    // Iterate in reverse order over the queue and put the elements into the vector.
    for(auto element = this->nodes.end(); element != this->nodes.begin(); --element){
        elements.push_back(*element);
    }

    return elements;       
}
// Functions for the Priority Queue.
tuple<int, float> PriorityQueue::pop(){

    // Get the top node from the min heap
    tuple<int, float> top_node = this->nodes.top();

    // Remove the top node
    this->nodes.pop();

    // Also remove the node from the is_in vector.
    this->is_in[get<0>(top_node)];

    return top_node;
}

// Add a new node into the Priority qeue.
// Find the correct position and insert it in both
// the nodes deqeue and the weight deqeue.
void PriorityQueue::add(int node, float weight){
    this->nodes.push(tuple<int, float>(node, weight));
    this->is_in[node] = true;
}

// Return the size of the queue
int PriorityQueue::size(){
    return this->nodes.size();
}

// Print the priority queue.
void PriorityQueue::print(){
    // Create a hard copy of the priority queue.
    auto local_copy =  priority_queue <tuple<int, float>, vector<tuple<int, float>>, GreaterNode>(this->nodes);
    tuple<int, float> tmp;
    while(local_copy.size() > 0){
        tmp = local_copy.top();
        cout << "(" << get<0>(tmp) << ", " << get<1>(tmp) << ") ->>";
        local_copy.pop();
    }
    cout << endl;
}

// is_empty returns wether the priority queue is empty.
// This is just for convenience
bool PriorityQueue::is_empty(){
    return this->size() == 0;
}
// Test wether node node is in the queue
bool PriorityQueue::contains(int node){
    this->is_in[node];
}

// Short logic to convert map to coordinate and vice versa
int coordinate2node(int x_coordinate, int y_coordinate, int dimensions_board){
    return x_coordinate * dimensions_board + y_coordinate;
}

int node2coordinate_x(int node, int dimensions_board){
    return node / dimensions_board;
}

int node2coordinate_y(int node, int dimensions_board){
    return node % dimensions_board;
}

bool is_in(int x_coordinate, int y_coordinate, int dimensions_board){
    // Test wether the coordinates would fall into the dimensions of the board

    // Test x_coordinate
        if (x_coordinate < 0) return false;
        if (x_coordinate >= dimensions_board) return false;

    // Test y_coordinate
        if (y_coordinate < 0) return false;
        if (y_coordinate >= dimensions_board) return false;
    
    return true;
}

bool not_in_deques(int node,  deque<int> deque1, deque<int> deque2){
    // Iterate over deque1
    for(int i = 0; i < deque1.size(); ++i){
        if(deque1[i] == node){
            return false;
        }
    }

    // Iterate over deque2
      for(int i = 0; i < deque2.size(); ++i){
        if(deque2[i] == node){
            return false;
        }
    }

    return true;
}

// Random integer
int rand_int(int begin, int end){
    int diff = end - begin;

    // Initiallize pseudo-random number generator.
    srand(time(nullptr));

    int random_integer = rand() % diff;
    return begin + random_integer;
}

int argmax(vector<float> values){
    int argmax = 0;
    for(int idx=0; idx<values.size(); ++idx){
        if (values[idx] > values[argmax]){
            argmax = idx;
        }
    }

    return argmax;
}