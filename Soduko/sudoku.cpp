/*
author: Tim Toebrock
Goals:
Implement a soduko class.
It should be able to
    - Create a valid, random soduko
    - Create a soduko from file
    - Check a soduko for correctness
    - Change positions in the soduko.
    - Get positions
    - Print out the soduko
*/

using namespace std;
#include<iostream>
#include<vector>

class Soduko{
    public:
    // Constructors:
        // Empty Constructor
        Soduko(){
            // Create a valid soduko, randomly 
            cout << "Not implemented yet!" << endl;
        }

        // Soduko from file
        Soduko(ifstream& graph_file){
            // Create the soduko from file.

        }

        Soduko(unsigned int val){
            // Create a Soduko with the value default in every element.
            for(auto rows: this->field){
                for(auto cols: rows){
                    cols = val;
                }
            }
        }

    // Getter & Setter of indival fields
    unsigned int get(int row, int col) const{
        return this->field[row][col];
    }

    void set(int row, int col, unsigned int val){
        this->field[row][col] = val;
    }

    // Print, both friend for external and and internal
    friend ostream& operator<<(ostream& out, Soduko& s);
    void print() const{
        cout << endl;
        for(int col = 0; col < this->field.size(); ++col){
            for(int row = 0; row < this->field.size(); ++row){
                if (( row % 3 == 0) && row != 0){
                    cout << "| ";
                }
                cout << this->field[row][col] << " ";
            }
            if (((col + 1) % 3 == 0) && col != 8){ // Dependen on array size.
                cout << endl;
                for(int i = 0; i < this->field.size() * 2 + 3; ++i){ // This is not independant of the size of the array.
                    cout << "-";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    // Check whether the Soduko is valid.
    bool valid() const{
        // Is the Soduko valid?
    }

    private:
    vector<vector<unsigned int> > field{vector<vector<unsigned int>>(9, vector<unsigned int>(9))};
};

// Overload << operator
ostream& operator<<(ostream& out, Soduko& s){
    // print out the soduko
}

int main(){
    Soduko p(9);
    p.print();
    return 0;
}