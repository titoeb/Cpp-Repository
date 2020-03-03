#include<iostream>
#include<random>
#include<ctime>
#include<limits>
#include<vector>
#include<deque>
#include<tuple>
#include<queue>

using namespace std;

// My implementation of a qeue that will only store elements. 
// It will used for the closed set later on.
// It will also store the order of nodes that were used in the minimal path.
class Queue{
    public:

        // Constructor only allocates the internal queue nodes.
        Queue(int n_nodes):nodes(deque<int>()), is_in(vector<bool>(n_nodes, false)){}

        // Add a new node into the queue.
        // Think of a new node entering the closed set.
        void add(int node){
            this->nodes.push_front(node);
            this->is_in[node] = true;
        }

        // is_empty returns wether the queue is empty.
        // This is just for convenience
        bool is_empty(){
            return this->size() == 0;
        }

        // Return the size of the queue
        int size(){
            return this->nodes.size();
        }

        // Test wether node node is in the queue
        bool contains(int node){
            return this->is_in[node];
        }

        // Return the elements in an vector.
        vector<int> elements(){

            // Initiallize to the accordings size
            vector<int> elements(this->size());

            // Iterate in reverse order over the queue and put the elements into the vector.
            for(auto element = this->nodes.end(); element != this->nodes.begin(); --element){
                elements.push_back(*element);
            }

            return elements;       
        }

    private:
        int n_nodes;
        deque<int> nodes; 

        // This vector will be use to make fast is_in operation.
        vector<bool> is_in;
};

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
        void add(int node, float weight){
            this->nodes.push(tuple<int, float>(node, weight));
            this->is_in[node] = true;
        }

        // Give the first nodes and its weight and remove it from the priority queue
        tuple<int, float> pop(){

            // Get the top node from the min heap
            tuple<int, float> top_node = this->nodes.top();

            // Remove the top node
            this->nodes.pop();

            // Also remove the node from the is_in vector.
            this->is_in[get<0>(top_node)];

            return top_node;
        }
        
        // Return the size of the queue
        int size(){
            return this->nodes.size();
        }

        // Print the priority queue.
        void print(){
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
        bool is_empty(){
            return this->size() == 0;
        }

        // Test wether node node is in the queue
        bool contains(int node){
            this->is_in[node];
        }

    private:
        priority_queue <tuple<int, float>, vector<tuple<int, float>>, GreaterNode> nodes; 
        vector<bool> is_in;
};

// This class will implement a graph based on an adjecency matrix
class Graph{
    public:

        // Empty Constructor:
        // Create a grpah without andy connections
        Graph(int n_nodes):n_nodes(n_nodes), verbose(0), n_vertices(0), values(vector<float>(n_nodes, 0.0)){

            // Allocate empty adjecency matrix.
            vector< vector<float> > a(n_nodes, vector<float>(n_nodes, numeric_limits<float>::max()));
            this->adjecency_matrix = a;
        }

        // Random Constructor:
        // This constructor creates a randomly generated graph.
        // density is the probability of a random edge to exist.
        // distance range is the range of the distance and are uniformly sampled from 0, distance_range
        Graph(int n_nodes, float density, float distance_range):n_nodes(n_nodes), verbose(0), n_vertices(0), values(vector<float>(n_nodes, 0.0)){


            // Initiallize the adjecency matrix.
            vector< vector<float> > a(n_nodes, vector<float>(n_nodes, numeric_limits<float>::max()));
            this->adjecency_matrix = a;

            // Initiallize the pseudo-random number generated to get different results each time the function is executed.
            mt19937 generator (time(0));

            // This sampler is used to sample the weights of the edges.
            uniform_real_distribution<float> distances(0.0, distance_range);

            // This sampler is used to determine whether a node will exist.
            uniform_real_distribution<float> select_edge(0.0, 1.0);

            // Create a random graph.
            // Iterate over all possible nodes, then decider whether is should exist, when it does
            // sample the random range.
            for(int node_1 = 0; node_1 < this->n_nodes; ++node_1){
                for(int node_2 = node_1 + 1; node_2 < this->n_nodes; ++node_2){

                    // Should this node exists
                    if (select_edge(generator) <= density){

                        // The node will exists, create a random edge weight.
                        this->set_edge(node_1, node_2, distances(generator));
                    }
                }
            }
        }

        // Set and Get functions
        // Insert another edge into the graph.
        void set_edge(int node_1, int node_2, float distance){
            // To put in another connection, this connection simply needs to be put into the adjecency matrix.
            this->adjecency_matrix[node_1][node_2] = this->adjecency_matrix[node_2][node_1] = distance;
            n_vertices += 1;
        }

        float get_edge(int node_1, int node_2){
            return this->adjecency_matrix[node_1][node_2];
        }

        void remove_edge(int node_1, int node_2){
            this->adjecency_matrix[node_1][node_2] = this->adjecency_matrix[node_2][node_1] = numeric_limits<float>::max();
            n_vertices -= 1;
        }

        // Get the node value of node node.
        float get_node_value(int node){
            return this->values[node];
        }

        // Set the node value of node node.
        void set_node_value(int node, float value){
            this->values[node] = value;
        }

        // Give the number of nodes
        int get_n_nodes(){
            return this->n_nodes;
        }

        // Give the number of vertices
        int get_n_vertices(){
            return this->n_vertices;
        }

        // Set verbosity level (used for debugging).
        void set_verbosity(int verbosity){
            this->verbose = verbosity;
        }

        bool is_adjacent(int node_1, int node_2){
            return (get_edge(node_1, node_2) != numeric_limits<float>::max());
        }

        vector<int> neighbors(int node){
            // Initiate empty vector.
            vector<int> neighbors;

            // Iterate over all nodes to find that one that are adjacent.
            for (int other_node = 0; other_node < this->n_nodes; ++other_node){
                if(this->is_adjacent(node, other_node)){
                    neighbors.push_back(other_node);
                }
            }

            // Return the vector conataining the neighbors that were found.
            return neighbors;
        }

        // Print method: Print out the connections that exists in the graph in the form:
        // node_1 <-- weight of connection --> node_2
        void print(){
            // go through all possible connections and print out the ones that exist.
            for(int node_1 = 0; node_1 < this->n_nodes; ++node_1){
                for(int node_2 = node_1 + 1; node_2 < this->n_nodes; ++node_2){
                    if (this->adjecency_matrix[node_1][node_2] != numeric_limits<float>::max()){
                        
                        // There is an edge between node1, node2. Print it!
                        cout << node_1 << " <--" << this->adjecency_matrix[node_1][node_2] << "--> " << node_2 << endl;
                    }
                }
            }

            // Finally add another new line for nicer outputs.
            cout << endl;
        }

        // Dijkstra's Shortest path algorithm.
        // Input two nodes and get the resulting distance.
        //  The implementation will be below.
        tuple<vector<int>, float> shortest_path(int node1, int node2);

        // This function implements the computation of the average path length in the graph.
        float average_path_length(){

            // This aggregator will hold the sum of the minimal distances
            float sum_length = 0.0;
            
            // Temporary variable to store the computed minimal distance between nodes.
            float min_dist;

            // Implementation of the average path length functions as asked for.
            // To compute the average path length compute the path length between 0 to 1, 0 to 2, ..., 0 to n
            for(int node = 1; node < this->n_nodes; ++node){

                // Compute the minimal distance.
                min_dist = get<1>(this->shortest_path(0, node));
                if (min_dist != -1.0){
                    // -1.0 means there was no path between 0, node,
                    // this is not the case so sum the found minimal distance to the aggregator.
                    sum_length = sum_length + min_dist;
                } else {
                    // There is no connection between node 0 and node node. Report this to the user!
                    cout << "ERROR! Did not find a way from node 1 to node " << node << "." << endl;
                }
            }

            // Finally Compute the average.
            return sum_length / (this->n_nodes - 1);
        }

    private:
        // The number of nodes the network has.
        int n_nodes;

        // The number of vertices.
        int n_vertices;

        //Additional message printed if verbose > 0, can be used for debugging.
        int verbose;

        // Vector containing the node values
        vector<float> values;

        // I use a connectivity matrix to describe the graph.
        // The weights of the edges will be stored in this matrix.
        // As this is an undirected graph, the matrix will be symmetric, e.g. mat[i, j] = mat[j, i]
        // Therefore, one could also implement a triangular matrix instead.
        vector<vector<float>> adjecency_matrix;
};

// Dijkstra's Shortest path algorithm.
// Input two nodes and get the resulting distance.
tuple<vector<int>, float> Graph::shortest_path(int node1, int node2){

    // Allocate open and closed set.
    PriorityQueue open_set(this->n_nodes);
    Queue closed_set(this->n_nodes);

    // Store the overall distance to.   
    float distance_to = 0.0;
    
    // tuple to hold the poped entries from the open set
    tuple<int, float> next_node;

    // Used to temporary store the node just retrieved from the open set.
    int node;

    // Store the neigbors of the node.
    vector<int> neighbors;

    // Begin with algorithm.
    // The algorithm is ended if either node2 is in the closed set, then its entry is the minimal distance from node1
    // or if the open set is empty is node2 is not in the close set. Then node2 is not reachable from node 1.
    open_set.add(node1, 0.0);

    // Iterate until either the open set is empty or the 
    while((!open_set.is_empty()) && (!closed_set.contains(node2))){
        
        // Get the minimal node from the auto set.
        next_node = open_set.pop();

        if(this->verbose > 0){
            cout << "next node: " << get<0>(next_node) << " at distance " << get<1>(next_node) << endl;
        }

        // Extract the node
        node = get<0>(next_node);

        // Check whether this node is already in the closed because duplicates can be in the open set!
        if(closed_set.contains(node)){

            // If the node is already in the closed set we don't need to consider it
            if(this->verbose > 0){
                cout << "Abortion because node " << node << " is already in the closed set." << endl;
            }
            continue;
        }

        // Put the node we just reached into the closed set and add the distance to the overall distance
        closed_set.add(node);
        distance_to = get<1>(next_node);

        // Put all nodes that are reachable from node into the open set.
        neighbors = this->neighbors(node);

        for(auto nb: neighbors){
            // Only put a node into the open set, if it is not already in the closed set
            if(!closed_set.contains(nb)){
                // Depending on whether the node is already in the open set, we either have to update its weight, or to inser it.
                open_set.add(nb, this->adjecency_matrix[node][nb] + get<1>(next_node));

                 if(this->verbose > 0){
                    cout << "Adding " << nb << " at " << this->adjecency_matrix[node][nb] + get<1>(next_node) << "." << endl;
                }
            }
        }
        if(this->verbose > 0){
            cout << "Open set: " << endl;
            open_set.print();
        }
    }

    if (closed_set.contains(node2)){
        // We found the minimal path from node1 to node2 and return it.
        return tuple<vector<int>, float>(closed_set.elements(), distance_to);

    } else {

        // There is not path from node1 to node2. Return error code -1.
        return tuple<vector<int>, float>(vector<int>(), -1.0);
    }
}

bool small_test(){
    Graph test = Graph(7);
    test.set_edge(0, 1, 7.0);
    test.set_edge(0, 2, 9.0);
    test.set_edge(0, 5, 14.0);
    test.set_edge(1, 2, 10.0);
    test.set_edge(1, 3, 15.0);
    test.set_edge(2, 5, 2.0);
    test.set_edge(2, 3, 11.0);
    test.set_edge(3, 4, 6.0);
    test.set_edge(4, 5, 9.0);

    // For more output change verbosity to 1.
    test.set_verbosity(0);

    auto result = test.shortest_path(0, 4);
    if (get<1>(result) != 20.0){
        cout << "Test 1: Result should be 20 but is " << get<1>(result) << endl;
        return false;
    }
    
    result = test.shortest_path(0, 1);
    if (get<1>(result) != 7.0){
        cout << "Test 1: Result should be 7.0 but is " << get<1>(result) << endl;
        return false;
    }
    
    result = test.shortest_path(0, 0);
    if (get<1>(result) != 0.0){
        cout << "Test 1: Result should be 0.0 but is " << get<1>(result) << endl;
        return false;
    }

    result = test.shortest_path(0, 3);
    if (get<1>(result) != 20.0){
        cout << "Test 1: Result should be 20.0 but is " << get<1>(result) << endl;
        return false;
    }

    result = test.shortest_path(5, 1);
    float min_dist = 12.0;
    if (get<1>(result) != min_dist){
        cout << "Test 1: Result should be " << min_dist << " but is " << get<1>(result) << endl;
        return false;
    }

    result = test.shortest_path(4, 2);
    min_dist = 11.0;
    if (get<1>(result) != min_dist){
        cout << "Test 1: Result should be " << min_dist << " but is " << get<1>(result) << endl;
        return false;
    }

    return true;
}

bool no_connection_test(){

     Graph test = Graph(3);
    test.set_edge(0, 1, 7.0);


    auto result = test.shortest_path(0, 2);
    auto min_dist = -1.0;
    if (get<1>(result) != min_dist){
        cout << "Test 1: Result should be " << min_dist << " but is " << get<1>(result) << endl;
        return false;
    }

    return true;

}
int main(){

    if(!small_test()){
        cout << "The test failed !!!" << endl;
    }

    if(!no_connection_test()){
        cout << "The no connection test failed !!!" << endl;
    }
    
    // Testing the implementaion of graph and average shortest path.
    Graph test_graph = Graph(10000, 0.001, 100.0);

    test_graph.set_verbosity(0);
    //float min_dist = test_graph.average_path_length();

    auto min_dist = test_graph.shortest_path(0, 10);
    cout << "The average path length is " << get<1>(min_dist) << "." << endl;
}