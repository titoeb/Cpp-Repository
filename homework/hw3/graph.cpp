#include <iostream>
#include <random>
#include <ctime>
#include <limits>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

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

class Graph{
    public:
        // Empty Constructor
        Graph(int n_nodes):n_nodes(n_nodes), verbose(0){
            // Allocate empty adjecency matrix.
            vector< vector<float> > a(n_nodes, vector<float>(n_nodes, numeric_limits<float>::max()));
            this->adjecency_matrix = a;
        }

        // Random Constructor
        Graph(ifstream& graph_file, int verbosity=0):verbose(verbosity){
            string line;
            int node_a, node_b;
            float cost;
            // Read n_nodes from file
            getline(graph_file, line);
            this->n_nodes = stoi(line);
            
            // Initiallize the adjecency matrix.
            vector< vector<float> > a(n_nodes, vector<float>(n_nodes, numeric_limits<float>::max()));
            this->adjecency_matrix = a;

            // Iterator through file and read in vertices with their respective costs.
            while(getline(graph_file, line)){
                // process line
                process_line(node_a, node_b, cost, line);
                // enter results into adjecency matrix.
                this->adjecency_matrix[node_a][node_b] = this->adjecency_matrix[node_b][node_a] = cost;
            }
        }

        Graph(int n_nodes, float density, float distance_range):n_nodes(n_nodes), verbose(0){
            // Initiallize the adjecency matrix.
            vector< vector<float> > a(n_nodes, vector<float>(n_nodes, numeric_limits<float>::max()));
            this->adjecency_matrix = a;
            // Initiallize the random sampler to get different results each time.
            mt19937 generator (time(0));

            // This is used to create random distances.
            uniform_real_distribution<float> distances(0.0, distance_range);

            // This is used to create and edge or not.
            uniform_real_distribution<float> select_edge(0.0, 1.0);

            // Create a random graph with the according distances:
            for(int node_1 = 0; node_1 < this->n_nodes; ++node_1){
                for(int node_2 = node_1 + 1; node_2 < this->n_nodes; ++node_2){
                    // Simulate the distance between node_1, node_2 with probability density
                    if (select_edge(generator) <= density){
                        this->adjecency_matrix[node_1][node_2] =  this->adjecency_matrix[node_2][node_1] = distances(generator);
                    } else {
                        // A distance of FLOAT_MAX does mean that there is no edge between two nodes.
                        this->adjecency_matrix[node_1][node_2] =  this->adjecency_matrix[node_2][node_1] = numeric_limits<float>::max();
                    }
                }
            }
        }

        // Set and get functions
        // Set Edge
        void set_edge(int node_1, int node_2, float distance){
            this->adjecency_matrix[node_1][node_2] = this->adjecency_matrix[node_2][node_1] = distance;
        }
        // Set verbosity
        void set_verbosity(int verbosity){
            this->verbose = verbosity;
        }

        // print_method
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
             cout << endl;
        }

        // Compute the minimum spanning tree
        float minimum_spanning_tree(){
            float distance = 0.0;
            float dist_tmp;
            int node_entered = 0;
            int nodes_in_open = 0;
            int min_node;

            // Buffer to save nodes that are already in the spanning tree or not.
            vector<float> open_set(this->n_nodes,  numeric_limits<float>::max());
            vector<bool> closed_set(this->n_nodes, false);

            // Put first node in the set.
            closed_set[0] = true;
            node_entered++;

            // Put all nodes reachable in the open set.
            for(int i = 0; i < this->n_nodes; i++){
                if((this->adjecency_matrix[0][i] >= 0) && (closed_set[i] == false)){
                    // node i is reachable and not yet in the minimum spanning tree
                    dist_tmp = this->adjecency_matrix[0][i];
                    if((dist_tmp < open_set[i]) || (open_set[i] ==  numeric_limits<float>::max())){
                        open_set[i] = dist_tmp;
                        nodes_in_open++;
                    }
                }
            }

            cout << "nodes entered: " << node_entered << ", nodes_in_open: " << nodes_in_open << endl;
            // Iterate either until all nodes are in the closed set
            // or some are not but their are no nodes reachable in the open set.
            while((node_entered < this->n_nodes) && (nodes_in_open > 0)){
                // Search for node with minimal distance in the open set.
                min_node = argmin(open_set);

                // Add it to the closed set.
                closed_set[min_node] = true;
                node_entered++;
                distance += open_set[min_node];
                cout << "Node " << min_node << " entered the closed set with distance " << open_set[min_node] << endl;
                open_set[min_node] =  numeric_limits<float>::max();
                nodes_in_open--;

                // Add new available node to open set.
                for(int i = 0; i < this->n_nodes; i++){
                    if((this->adjecency_matrix[min_node][i] >= 0) && (closed_set[i] == false)){
                        // node i is reachable and not yet in the minimum spanning tree
                        dist_tmp = this->adjecency_matrix[min_node][i];
                        if((dist_tmp < open_set[i]) || (open_set[i] == numeric_limits<float>::max())){
                            if (open_set[i] == numeric_limits<float>::max()) nodes_in_open++;
                            open_set[i] = dist_tmp;
                        }
                    }
                }        
            }
            // Finally test whether the algorithm was succesful
            if (node_entered == this->n_nodes){
                return distance;
            } else {
                return -1.0;
            }
        }

        // Compute the minimal distance between node1, node2
        float min_distance(int node1, int node2){

            // Allocate open and closed set.
            float open_set[this->n_nodes];
            float closed_set[this->n_nodes];
            int n_open = 0;
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
            while((n_open > 0) && (closed_set[node2] < 0)){
                // Find the minimum in open set
                minimal_node = give_min(open_set, closed_set, this->n_nodes);
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

        float average_path_length(){
            float sum_length = 0.0;
            float min_dist;
            for(int node = 1; node < this->n_nodes; ++node){
                min_dist = min_distance(0, node);
                if (min_dist != -1.0){
                    sum_length = sum_length + min_dist;
        // Used for debug printouts. ist;
                } else {
                    cout << "ERROR! Did not find a way from node 1 to node " << node << "." << endl;
                }
            }
            return sum_length / (this->n_nodes - 1);
        }

    private:
        // How many nodes are in the network
        int n_nodes;
        //Additional message printed if verbose > 0.
        int verbose;

        // The weights of the matrix, as the graph is undirected, the array will be symmetric.
        // Therefore, one could also implement a triangular matrix instead.
        vector<vector<float>> adjecency_matrix;
};


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
    Graph test_graph(word_file, 1);
    test_graph.print();

    float dist_min_spanning_tree = test_graph.minimum_spanning_tree();
    cout << "minimal spanning tree has length dist: " << dist_min_spanning_tree << endl;
}