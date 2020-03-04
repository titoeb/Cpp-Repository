#include<iostream>
#include<random>
#include<ctime>
#include<limits>
#include<fstream>
#include<iterator>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<deque>
#include<tuple>

using namespace std;

float give_min(const float* min_array, const float* exclude_array, int n_nodes){
    float min = numeric_limits<float>::max();
    int min_pos = -1;
    for(int i = 0; i < n_nodes; ++i){
        if((min_array[i] < numeric_limits<float>::max()) && (exclude_array[i] == numeric_limits<float>::max()) && (min_array[i] < min)){
            min = min_array[i];
            min_pos = i;
        }
    }
    return min_pos;
}

int argmin(vector<float> input){
    int min_node = 0;
    float current_min = numeric_limits<float>::max();
    for(int i = 0; i<input.size(); ++i){
        if ((input[i] < current_min)){
            min_node = i;
            current_min = input[i];
        }
    }
    return min_node;
}

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
// Read in a single line
void process_line(int& node_a, int& node_b, float& cost, const string& line){
    istringstream input(line);
    string word;
    getline(input, word, ' ');
    node_a = stoi(word);
    getline(input, word, ' ');
    node_b = stoi(word);

    getline(input, word, ' ');
    cost = static_cast<float> (stoi(word));
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

        // From file constructor
        Graph(ifstream& graph_file, int verbosity=0):verbose(verbosity){
            string line;
            int node_a, node_b;
            float cost;
            // Read n_nodes from file
            getline(graph_file, line);
            this->n_nodes = stoi(line);
            
            // Initiallize the adjecency matrix.
            vector< vector<float> > a(this->n_nodes, vector<float>(this->n_nodes, numeric_limits<float>::max()));
            this->adjecency_matrix = a;

            // Iterator through file and read in vertices with their respective costs.
            while(getline(graph_file, line)){
                // process line
                process_line(node_a, node_b, cost, line);
                // enter results into adjecency matrix.
                this->adjecency_matrix[node_a][node_b] = this->adjecency_matrix[node_b][node_a] = cost;
            }
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

        // This function computes the length of the spanning tree
        tuple<float, vector<int>> minimum_spanning_tree();

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

tuple<float, vector<int>> Graph::minimum_spanning_tree(){
    float distance = 0.0;
    float dist_tmp;
    int node_entered = 0;
    int nodes_in_open = 0;
    int min_node;

    vector<int> neighbors;

    // Buffer to save nodes that are already in the spanning tree or not.
    vector<float> open_set(this->n_nodes,  numeric_limits<float>::max());
    Queue closed_set(this->n_nodes);

    // Put first node in the set.
    closed_set.add(0);

    // Put all nodes reachable in the open set.
    neighbors = this->neighbors(0);

    for(auto element = neighbors.begin(); element != neighbors.end(); ++element){
        open_set[*element] = this->adjecency_matrix[0][*element];
        ++nodes_in_open;
    }

    if(this->verbose > 0){
        cout << "nodes entered: " << node_entered << ", nodes_in_open: " << nodes_in_open << endl;
    }

    // Iterate either until all nodes are in the closed set
    // or some are not but their are no nodes reachable in the open set.
    while((closed_set.size() < this->n_nodes) && (nodes_in_open > 0)){

        // Search for node with minimal distance in the open set.
        min_node = argmin(open_set);

        // Add it to the closed set.
        closed_set.add(min_node);
        node_entered++;

        distance += open_set[min_node];
        if(this->verbose > 0){
            cout << "Node " << min_node << " entered the closed set with distance " << open_set[min_node] << endl;
        }
        open_set[min_node] =  numeric_limits<float>::max();
        nodes_in_open--;

        // Add new available node to open set.
        neighbors = this->neighbors(min_node);

        for(auto element = neighbors.begin(); element != neighbors.end(); ++element){
            if(!closed_set.contains(*element) && open_set[*element] > this->adjecency_matrix[min_node][*element]){
                open_set[*element] = this->adjecency_matrix[min_node][*element];
                ++nodes_in_open;
            }   
        }
    }

    // Finally test whether the algorithm was succesful
    if (closed_set.size() == this->n_nodes){
        return tuple<float, vector<int>>(distance, closed_set.elements());
    } else {
        return  tuple<float, vector<int>>(-1.0, vector<int>());
    }
}

int main(){
    // Testing the implementaion of graph and average shortest path.
    /* 
    Graph test_graph = Graph(1000, 0.4, 100.0);

    //test_graph.set_verbosity(1);
    float min_dist = test_graph.average_path_length();
    cout << "The average path length is " << min_dist << "." << endl; */

    // Testing the implementation of the minimum spanning tree
    /*Graph test_graph = Graph(4);
    test_graph.set_edge(0, 1, 5.0);
    test_graph.set_edge(0, 3, 4.0);
    test_graph.set_edge(1, 2, 2.0);
    test_graph.set_edge(1, 3, 3.0);
    test_graph.set_edge(2, 3, 1.0);
    cout << test_graph.minimum_spanning_tree() << endl; */

    // String that will contain file_name to load graph from.
    string file_name("test.txt");
    //cout << "Please give the file from which the graph should be created!" << endl;
    //cin >> file_name;
    //cout << file_name << endl;
    ifstream word_file(file_name);
    Graph test_graph(word_file, 0);
    test_graph.print();

    //float dist_min_spanning_tree = test_graph.minimum_spanning_tree();
    float other_dist = get<0>(test_graph.minimum_spanning_tree());

    // Result should be 33
    cout << "33 = " << other_dist << endl;
}