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
            
        }

        // Soduko from file
        Soduko(ifstream& graph_file){
            // Create the soduko from file.
            cout << "Not implemented yet!" << endl;
        }

        Soduko(unsigned int val){
            // Create a Soduko with the value default in every element.
            for(auto rows: this->field){
                for(auto cols: rows){
                    cols = val;
                }
            }
        }

        // Boolean check soduko
        bool check(){
            // Check whether the soduko is valid.

            // Check the rows
            for (int row = 0; row < 9; ++row){
                if(check_row(this, row) == false) return false;
            }

            // Check the columns

            // Check the squares

            return true;

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
    // The Array itself
    vector<vector<unsigned int> > field{vector<vector<unsigned int>>(9, vector<unsigned int>(9))};

    // Additional helper methods
    bool check_row(Soduko* s, int row){
        vector<bool> d(10, 0);  
        for(int col = 0; col < 9; ++col){
            d[s->get(row, col)] = true;
        }

        for(int number = 1; number < 10; ++number){
            if (d[number] == false){
                return false;
            }
        }

        return true;
    }

    bool check_col(Soduko* s, int col){
        vector<bool> d(10, 0);
        for(int row = 0; row < 9; ++row){
            d[s->get(row, col)] = true;
        }

        for(int number = 1; number < 10; ++number){
            if (d[number] == false){
                return false;
            }
        }

        return true;
    }

    bool check_square(Soduko* s, int square){
    vector<bool> d(10, 0);
    int start_col = square * 3;
    int end_col = (square + 1) * 3;

    int start_row = (square / 3) * 3;
    int end_row = ((square / 3) + 1) * 3;

    for(int row = start_row; row < end_row; ++row){
        for(int col = start_col; col < end_col; ++col){
            d[s->get(row, col)] = true;
        }
    }

    for(int number = 1; number < 10; ++number){
        if (d[number] == false){
            return false;
        }
    }

    return true;
    }
};

// Overload << operator
ostream& operator<<(ostream& out, Soduko& s){
          cout << endl;
        for(int col = 0; col < s.field.size(); ++col){
            for(int row = 0; row < s.field.size(); ++row){
                if (( row % 3 == 0) && row != 0){
                    cout << "| ";
                }
                cout << s.field[row][col] << " ";
            }
            if (((col + 1) % 3 == 0) && col != 8){ // Dependen on array size.
                cout << endl;
                for(int i = 0; i < s.field.size() * 2 + 3; ++i){ // This is not independant of the size of the array.
                    cout << "-";
                }
            }
            cout << endl;
        }
        cout << endl;
        return out;
    }


int main(){
    Soduko p(9);
    p.print();
    cout << "chekc: " << p.check() << endl;
    return 0;
}