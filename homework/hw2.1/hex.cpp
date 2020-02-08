#include<iostream>

using namespace std;

enum class Player{P1, P2, Empty};

class Board{
    public:
        // constructor
        Board(int size):size(size){
            // Create a board of size size
        }

        // print method
        void print(){

        }

        // Getter and setter
        Player get_position(int row, int col){
            // Get the element from the stupid graph structure.

        }

        void set_position(int row, int col, Player p){
            // Set an element in the stupid graph structure.
            
        }

    private:
        // Size of the hex board
        int size;
        // The hex board itself 
};


void play_hex(int size){
    Board b(size);

}


int main(){
    int size;
    cout << "Welcome the game of hash." << endl;
    cout << "Please insert the size of the board. The size should be more than 1." << endl;
    cin >> size;

    play_hex(size);
}