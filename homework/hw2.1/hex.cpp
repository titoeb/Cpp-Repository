#include "hex.h"

    Hex::Hex(int size):size(size), PlayerRed(hexGraph(size)), PlayerBlue(hexGraph(size)){}

    // print method
    void Hex::print(){
        for(int row=0; row < this->size; ++row){
            // Print spaces in the beginning
            for(int n_spaces=0; n_spaces < 2 * row; ++n_spaces) cout << ' ';

            // Print out the actual fields of the array.
            for(int col=0; col<this->size; ++col){
                if(this->PlayerBlue.node_exists(row, col)){
                    cout << 'X';
                } else {
                    if(this->PlayerRed.node_exists(row, col)){
                        cout << 'O';
                    } else {
                        cout << '.';
                    }
                }
                if (col < this->size -1 ) cout << " - ";
            }
            cout << endl;
            // Draw intermediate line if we are not in the last row.
            if (row < this->size - 1){
                // Draw spaces
                for(int n_spaces=0; n_spaces < 1 + 2 * row; ++n_spaces) cout << ' ';
                // Draw intermediate line.
                for(int i = 0; i < this->size-1; i++){
                    cout << "\\ / ";
                }
                cout << "\\" <<endl;
            }
        }
    }

    // Check whether game is over
    bool Hex::game_over(){
        return player_blue_won() || player_red_won(); 
    }

    bool Hex::player_red_won(){
        // Check if upper side is connect to down side or the lift side to the ride side.
        for(int i = 0; i < this->size; ++i){
            for(int j = 0; j < this->size; ++j){
                if(PlayerRed.is_connected(0,i,(this->size - 1), j) || PlayerRed.is_connected(i, 0, j, (this->size - 1))) return true;
            }
        }

        return false;
    }

    bool Hex::player_blue_won(){
        // Check if upper side is connect to down side or the lift side to the ride side.
        for(int i = 0; i < this->size; ++i){
            for(int j = 0; j < this->size; ++j){
                if(this->PlayerBlue.is_connected(0,i,(this->size - 1), j) || this->PlayerBlue.is_connected(i, 0, j, (this->size - 1))) return true;
            }
        }

        return false;

    }

    // Add nodes for users
    bool Hex::add_node_red(int node_x, int node_y){
        // Check whether blue has this node
        if (this->PlayerBlue.node_exists(node_x, node_y) || this->PlayerRed.node_exists(node_x, node_y)){
            return false;
        } else {
            // Check whether the node is within the boundaries.
            if(is_in(node_x, node_x, this->size)){
                // Add the node
                this->PlayerRed.addNode(node_x, node_y);
                return true;
            } else {
                // The move is illegal because the node is not in the field
                return false;
            }
        }
    }

    bool Hex::add_node_blue(int node_x, int node_y){
          // Check whether blue has this node
        if (this->PlayerBlue.node_exists(node_x, node_y) || this->PlayerRed.node_exists(node_x, node_y)){
            return false;
        } else {
            // Check whether the node is within the boundaries.
            if(is_in(node_x, node_x, this->size)){
                // Add the node
                this->PlayerBlue.addNode(node_x, node_y);
                return true;
            } else {
                // The move is illegal because the node is not in the field
                return false;
            }
        }
    }
