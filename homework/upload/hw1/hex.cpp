#include "hex.h"
// Constructor
Hex::Hex(int size, PlayerType player_blue, PlayerType player_red):size(size),player_type_X(player_blue), player_type_O(player_red), PlayerO(hexGraph(size)), PlayerX(hexGraph(size)){}

// print method
void Hex::print(){
    for(int row=0; row < this->size; ++row){
        // Print spaces in the beginning
        for(int n_spaces=0; n_spaces < 2 * row; ++n_spaces) cout << ' ';

        // Print out the actual fields of the array.
        for(int col=0; col<this->size; ++col){
            if(this->PlayerX.node_exists(row, col)){
                cout << 'X';
                if(this->PlayerO.node_exists(row, col)){
                    cout << "This can't be! node " << row << ", " << col << " exists for X and 0!" << endl;
                }
            } else {
                if(this->PlayerO.node_exists(row, col)){
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
bool Hex::X_won(){
    return PlayerX.sides_connected();
}

bool Hex::O_won(){
    return PlayerO.sides_connected();
}

void Hex::player_O_turn(){
    this->take_turn(this->PlayerO, this->player_type_O, this->PlayerX);
}
        
void Hex::player_X_turn(){
    this->take_turn(this->PlayerX, this->player_type_X, this->PlayerO);
}

bool Hex::add_node(hexGraph& this_player, hexGraph& other_player, int node_x, int node_y){
    if(this_player.node_exists(node_x, node_y) || other_player.node_exists(node_x, node_y)){
        return false;
    } else {
        this_player.addNode(node_x, node_y);
        return true;
    }
}

void Hex::take_turn(hexGraph& player, PlayerType player_type, hexGraph& other_player){
    if (player_type ==  PlayerType::HUMAN){
        Hex::user_move(player, other_player);
    } else {
        if (player_type == PlayerType::STUPIDAI){
            Hex::random_ai(player, other_player);
        } else {
                cout << "PlayerType Type cannot be " << static_cast<int>(player_type) << endl;
        }
    }
}

// User moves.
void Hex::user_move(hexGraph& player, hexGraph& other_player){ 
    bool correct_move = false;
    int row, col;

     while(!correct_move){
        // Sample random action
        cout << "Which row do you want to set?" << endl;
        cin >> row;
        cout << "Which col do you want to set?" << endl;
        cin >> col;

        // Try to add the node the user wanted to add.
        correct_move = this->add_node(player, other_player, row, col);

        // If the move could not be taken, e.g.
            // -> the node is already set
            // -> the node is set for the other player
        // Give error message, loop is going to be repeated.
        if (!correct_move){
            cout << "Unfortunately, you cant set point (" << row << ", " << col << "). Please make another choice!" << endl;
        }
    }

}

vector<int> Hex::viable_moves(){
    vector<int> free_nodes;

    // Get all free entries of the field 
    for(int row=0; row<this->size; ++row){
        for(int col=0; col<this->size; ++col){
            if(!(this->PlayerO.node_exists(row, col) || this->PlayerX.node_exists(row, col))){
                free_nodes.push_back(coordinate2node(row, col, this->size));
            }
        }
    }
    return free_nodes;
}

void Hex::random_ai(hexGraph& player, hexGraph& other_player){
    bool correct_move = false;
    vector<int> free_nodes = this->viable_moves();

    // Sample a random entry from found missing entries.
    int random_position = rand_int(0, free_nodes.size());

    // Add the node at the random position to the player.
    player.addNode(free_nodes[random_position]);
}