#include<iostream>
#include<random>
#include<ctime>
#include<limits>
#include<vector>
#include<deque>

using namespace std;



// My implementation of a qeue that will only store elements. 
// It will used for the closed set later on.
// It will also store the order of nodes that were used in the minimal path.
class Queue{
    public:

        // Constructor only allocates the internal queue nodes.
        Queue():nodes(deque<int>()){}

        // Add a new node into the queue.
        // Think of a new node entering the closed set.
        void add(int node){
            this->nodes.push_front(node);
        }


        // Return the size of the queue
        int size(){
            return this->nodes.size();
        }

        // Test wether node node is in the queue
        bool contains(int node){
            // Iterate over the queue.
            // It we find the element, return the finding, else report not found.
            for(auto element: this->nodes){
                if(element == node){
                    return true;
                }
            }

            // We did not find node node and therefore, the node is not in the queue.
            return false;
        }

        // Return the elements in an vector.
        vector<int> elements(){

            // Initiallize to the accordings size
            vector<int> elements(this->size);

            // Iterate in reverse order over the queue and put the elements into the vector.
            for(auto element = this->nodes.end(); element != this->nodes.begin(); --element){
                elements.push_back(*element);
            }

            return elements;       
        }

    private:
        deque<int> nodes; 
};



// this is a helper function used in the min_distance function.
// It findes the minimum from the min_array array and only takes those position into account,
// that don't have a float:max in the exclude array.
// Both arrays are assumed to be of size n_nodes.
float give_min(const float* min_array, const float* exclude_array, int n_nodes){

    // The minimum is initiated to the largest possible value.
    float min = numeric_limits<float>::max();

    // The position of the minimum ist initiated to an impossible value.
    int min_pos = -1;

    // Iterate over the array
    for(int i = 0; i < n_nodes; ++i){
        // Three conditions have to load to find a new smallest value:
        // 1) the position does not have to be float:max in the min_array (node is in the open set)
        // 2) the positions does have to be float:max in the exclude array (node is not in the closed set)
        // 3) Is is a new minimum.
        if((min_array[i] < numeric_limits<float>::max()) && (exclude_array[i] == numeric_limits<float>::max()) && (min_array[i] < min)){
            
            // There is a new mininum, overwrite the old one.
            min = min_array[i];
            min_pos = i;
        }
    }

    // Return the position of the minumum,
    // if no valid minimum was found, return -1.0
    return min_pos;
}

// Find the position of the minimum in the vector input.
int argmin(vector<float> input){

    // Current position of the minimum
    int min_node = -1;

    // Current minimum
    float current_min = numeric_limits<float>::max();

    // Iterate over input to find the new minimum.
    for(int i = 0; i<input.size(); ++i){
        if ((input[i] < current_min)){
            min_node = i;
            current_min = input[i];
        }
    }
    return min_node;
}



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

            cout << "Starting! " << endl;

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
        float min_distance(int node1, int node2); 

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
                min_dist = this->min_distance(0, node);
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
float Graph::min_distance(int node1, int node2){

            // Allocate open and closed set.
            float open_set[this->n_nodes];
            float closed_set[this->n_nodes];

            // Number of variables in the open set
            int n_open = 0;

            // Minimal distance and the node.
            int minimal_node = -1;
            float distance_to = 0.0;

            // Make all entries to zero
            for(int i = 0; i< this->n_nodes; ++i){
                open_set[i] =  numeric_limits<float>::max();
                closed_set[i] =  numeric_limits<float>::max();
            }

            // Begin with algorithm.
            // The algorithm is ended if either node2 is in the closed set, then its entry is the minimal distance from node1
            // or if the open set is empty is node2 is not in the close set. Then node2 is not reachable from node 1.
            n_open = 1;
            open_set[node1] = 0.0;
            while((n_open > 0) && (closed_set[node2] == numeric_limits<float>::max())){
                // Find the minimum in open set
                minimal_node = give_min(open_set, closed_set, this->n_nodes);
                cout << "minimal node: " << minimal_node << endl;

                if (minimal_node != -1){
                    // Remove the minimal node from the open set to the closed set. 
                    closed_set[minimal_node] = open_set[minimal_node];

                    // Add all the reachable nodes to the 
                    for(int reachable_node = 0; reachable_node < this->n_nodes; ++reachable_node){
                        // Based on this node the distance to node reachable node is defined in the following
                        distance_to = this->adjecency_matrix[minimal_node][reachable_node] + open_set[minimal_node];

                        // There are three conditions so that we overwrite / set the value of the reachable node in the open set:
                        // 1) The reachable node is reachable from the minimal node we are looking at.
                        // 2) The reachable node is not in the closed set, then it would be irrelevant
                        // 3) Either the reachable node was not set in the open set or the path via the minimal node is smaller than the path to the reachable node that is currently in the open set.
                        if((this->adjecency_matrix[minimal_node][reachable_node] >= 0.0) && (closed_set[reachable_node] ==  numeric_limits<float>::max()) && ((distance_to < open_set[reachable_node]) || open_set[reachable_node] == numeric_limits<float>::max())){
                            open_set[reachable_node] = distance_to;
                             // Some print out for debug
                            if (this->verbose > 0){
                                cout << "Added node " << reachable_node << " to the open set at " << open_set[reachable_node] << " ." << endl;
                            }
                            
                            n_open = n_open + 1;
                        }
                    }

                    // Some print out for debug
                    if (this->verbose > 0){
                        cout << "Added node " << minimal_node << " to the closed set at " << open_set[minimal_node] << "." << endl;
                        cout << endl;
                    }
                    
                    open_set[minimal_node] = numeric_limits<float>::max();
                    n_open = n_open - 1;
                }
            }

            if (closed_set[node2] >= 0){
                // We found the minimal path from node1 to node2 and return it.
                return closed_set[node2];
            } else {
                // There is not path from node1 to node2. Return error code -1.
                return -1.0;
            }
        }


int main(){
    // Testing the implementaion of graph and average shortest path.
    Graph test_graph = Graph(1000, 0.4, 100.0);


    test_graph.set_verbosity(1);
    //float min_dist = test_graph.average_path_length();

    float min_dist = test_graph.min_distance(0, 10);
    cout << "The average path length is " << min_dist << "." << endl;
}