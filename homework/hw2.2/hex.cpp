#include "hex.h"

Hex::Hex(int size, Player player_blue, Player player_red):size(size),player_blue(player_blue), player_red(player_red), PlayerRed(hexGraph(size)), PlayerBlue(hexGraph(size)){}
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
bool Hex::blue_won(){
    return PlayerBlue.sides_connected();
}

bool Hex::red_won(){
    return PlayerRed.sides_connected();
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

// Simulate the turns for the players.
void Hex::player_red_turn(){
     if (this->player_red == Player::HUMAN){
        Hex::user_move(0);
    } else {
        if (this->player_red == Player::STUPIDAI){
            Hex::random_ai(0);
        } else {
            cout << "Player cannot be " << static_cast<int>(this->player_red) << endl;
        }
    }
}
void Hex::player_blue_turn(){
    if (this->player_blue ==  Player::HUMAN){
        Hex::user_move(1);
    } else {
        if (this->player_blue == Player::STUPIDAI){
            Hex::random_ai(1);
        } else {
            cout << "Player cannot be " << static_cast<int>(this->player_blue) << endl;
        }
    }
}

// User moves.
void Hex::user_move(int player){ 
    bool correct_move = false;
    int row, col;

     while(!correct_move){
        // Sample random action
        cout << "Which row do you want to set?" << endl;
        cin >> row;
        cout << "Which col do you want to set?" << endl;
        cin >> col;

        if (player == 0){
            // This is player Red
            correct_move = Hex::add_node_red(row, col);
        } else {
            if (player == 1){
                // This is player Blue
                correct_move = Hex::add_node_blue(row, col);
            } else {
                cout << "cannot take action for player " << player << " only 0, 1 are valid values." << endl;
                return;
            }
        }
        if (!correct_move){
            cout << "Unfortunately, you cant set point (" << row << ", " << col << "). Please make another choice!" << endl;
        }
    }

}
void Hex::random_ai(int player){
    bool correct_move = false;
    int row, col;

    while(!correct_move){
        // Sample random action
        row = rand_int(0, this->size);
        col = rand_int(0, this->size);

        if (player == 0){
            // This is player Red
            correct_move = Hex::add_node_red(row, col);
        } else {
            if (player == 1){
                // This is player Blue
                correct_move = Hex::add_node_blue(row, col);
            } else {
                cout << "cannot take action for player " << player << " only 0, 1 are valid values." << endl;
                return;
            }
        }
    }
}