#include <iostream>
#include <random>

using namespace std;

// Create a random probabilites generator

class adjecency_matrix{
    public:
        // Constructor: Allocate and either randomly initiate the underying matrix or allocate it random
        adjecency_matrix(int nodes, bool random=false, float probability=0.5):nodes(nodes){
            // Allocate the underlying bool matrix
            this->matrix = new bool*[this->nodes];
            for(int i = 0; i < this->nodes; ++i){
                this->matrix[i] = new bool[nodes];
            }

            // If random alloate them with random entries, otherwise empty:
            if (random == true){
                // Random allocation of edges
                // Set random generator.
                srand(time(0));

                // Set edges to random values
                for(int i = 0; i < this->nodes; ++i){
                    for(int j = i+1; j < this->nodes; ++j){
                        if (rand() > probability){
                            this->matrix[i][j] =  this->matrix[j][i] = true;
                        }
                        else{
                            this->matrix[i][j] =  this->matrix[j][i] = false;
                        }
    
                    }
                }
            } else {
                // all entries as zeros
                for(int i = 0; i < this->nodes; ++i){
                    for(int j = 0; j < this->nodes; ++j){
                        this->matrix[i][j] = false;
                    }
                }

            }
        }

        // Destructor: Dealloate the underlying boolean matrix
        ~adjecency_matrix(){
            for(int i = 0; i < this->nodes; ++i){
                delete this->matrix[i];
            }
            delete this->matrix;
        }

        // Getter and Setter for variables.
        int getNodes(){
            return this->nodes;
        }

        void setEdge(int i, int j, bool edge=true){
            this->matrix[i][j] = this->matrix[j][i] = edge;
        }

        bool getEdge(int i, int j){
            return this->matrix[i][j];
        }

        bool is_connected(){
            /*
                This algorithms checks whether the graph is connected, e.g. all nodes are connected.
            */
            int old_size = 0, closed_set_size = 0;
            bool found_one;

            // Allocate memory for the open and closed set.
            bool* open_set  = new bool[this->nodes];
            bool* closed_set  = new bool[this->nodes];
            // Initiallize all sets to be empty.
            for(int i = 0; i < this->nodes; ++i){
                open_set[i] = closed_set[i] = false;
            }
            // The first node is in the open set. (Each other node would do.)
            open_set[0] = true;
            closed_set_size = 1;

            // Main loop that looks for all connections.
            while(closed_set_size < this->nodes){
                found_one = false;
                // Check whether there is a node in the open set.
                for(int i = 0; i < this->nodes; ++i){
                    // Check for an open node.
                    if (open_set[i] == true){
                        // Found an node in the open set.
                        // is it already in the closed set?
                        if (closed_set[i] == false){
                            // It is not yet in the closed set.
                            closed_set[i] = true;
                            closed_set_size++;

                            // add all the nodes node i is connected to to the closed set.
                            for(int j = 0; j < this->nodes; ++j){
                                if ((this->matrix[i][j] == true) && (closed_set[j] == false)){
                                    open_set[j] = true;
                                    found_one = true;
                                }
                            }
                            // Iteration is ended succesfully, we put something in the closed set.
                            open_set[i] = false;
                            break;

                        } else {
                            // It was already in the closed set.
                            open_set[i] = false;
                            // If we found no other node in the open set that is not already in the closed set 
                            // and closed_set_size < this->nodes the graph is not connected.
                        }
                    }
                }
                // If we did not put anything in the closed set and this was not the final iteration, the graph is not complete.
                if ((found_one == false) && (closed_set_size < this->nodes)) return false;
            }
            // If we ended up here, we put all nodes in the closed set and the graph is connected.
            return true;


            delete open_set, closed_set;
        }

    private:
        int nodes;
        bool** matrix;
};

int main(){
    cout << "Testing the is_connected algorithm of the adjecency matrix clas" << endl;
    cout << "In the following two test cases are run." << endl;

    // Test case connected graph.
    cout << "Test for a connected graph" << endl;

    adjecency_matrix test1 = adjecency_matrix(6);
    test1.setEdge(0, 4);
    test1.setEdge(3, 1);
    test1.setEdge(1, 4);
    test1.setEdge(4, 2);
    test1.setEdge(2, 5);

    cout << "The graph said it was " << test1.is_connected() << " ." << endl;

    // Test case not connected graph
    cout << "Test for a not-connected graph" << endl;
    adjecency_matrix test2 = adjecency_matrix(4);
    test2.setEdge(0, 1);
    test2.setEdge(2, 3);
    cout << "The graph said it was " << test2.is_connected() << " ." << endl;
    return 0;
}