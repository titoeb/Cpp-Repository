#include "hex.h"

bool simulate_move(hexGraph this_player, hexGraph other_player, vector<int> viable_moves,  int move, int board_size){
    
    // Add the move to the player node.
    this_player.addNode(move);

    // Shuffle the viable moves.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(viable_moves.begin(), viable_moves.end(), std::default_random_engine(seed));
    int move_count = 0;

    // Add all moves from the viable moves to the board
    for(auto move_to_add: viable_moves){
        if(move_to_add != move){
            if(move_count % 2 == 0){
                other_player.addNode(move_to_add);
            } else {
                this_player.addNode(move_to_add);
            }
            ++move_count;
        }
    }
    // Check who has won the game.
    return this_player.sides_connected();
}

// Outer loop for monte - carlo simulation, simulate all moves between moves_begin and moves_end
// and store the resulting winning probabilites between winning_probablities_begin and 
// winnning_probabilites_end
void simulate_moves(hexGraph this_player, 
        hexGraph other_player,
        vector<int> viable_moves,
        vector<int>::iterator moves_begin,
        vector<int>::iterator moves_end,
        vector<float>::iterator winning_probabilites_begin,
        vector<float>::iterator winning_probabilites_end,
        int n_simulations,
        int board_size){
    
    int win_count = 0;

    // For each loop iteration, one potential move will be simulated
    while(moves_begin != moves_end){
        win_count = 0;

        for(int n_simulation=0; n_simulation < n_simulations; ++n_simulation){
            // Each loop is one monte carlo simulation.
            // If the player won add it to the win count
            win_count += static_cast<int>(simulate_move(this_player, other_player, viable_moves, *moves_begin, board_size));
        }

        // compute the winning fraction and put it into the winning probabilites
        *winning_probabilites_begin = static_cast<float>(win_count) / static_cast<float>(n_simulations);

        ++moves_begin;
        ++winning_probabilites_begin;
    }
}

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
            if(player_type == PlayerType::SMARTAI){
                Hex::monte_carlo_ai(player, other_player);
            } else{
                cout << "PlayerType Type cannot be " << static_cast<int>(player_type) << endl;
            }
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

void Hex::monte_carlo_ai(hexGraph& player, hexGraph& other_player){
    // Find viable moves
    vector<int> viable_moves = this->viable_moves();
    vector<float> winning_probabilites = vector<float>(viable_moves.size(),std::numeric_limits<float>::min());

    // For all viable moves simulate winning percentage
    if(N_THREADS >= 1){
        // This array will store all threads
        thread all_threads[N_THREADS];

        // This is the number of moves each thread will simulate.
        int stepsize = viable_moves.size() / N_THREADS;

        // With these iterators we will move trough the viable moves and winning probabilites
        vector<int>::iterator moves_position = viable_moves.begin();
        vector<float>::iterator winning_probabilites_position = winning_probabilites.begin();

        // Create all threads
        for(int n_thread = 0; n_thread < N_THREADS; ++n_thread){
            if (n_thread < N_THREADS - 1){
                all_threads[n_thread] = thread(simulate_moves, player, other_player, viable_moves, moves_position, moves_position+stepsize, winning_probabilites_position, winning_probabilites_position+stepsize, N_SIMULATIONS, this->size);

                moves_position += stepsize;
                winning_probabilites_position += stepsize;
            } else {
                // This is the final thread.
                all_threads[n_thread] = thread(simulate_moves, player, other_player, viable_moves, moves_position, viable_moves.end(), winning_probabilites_position, winning_probabilites.end(), N_SIMULATIONS, this->size);
            }
        }

        // Join all threads.
        for(int n_thread = 0; n_thread< N_THREADS; ++n_thread){
            all_threads[n_thread].join();
        }
        
    } else {
        simulate_moves(player, other_player, viable_moves, viable_moves.begin(), viable_moves.end(), winning_probabilites.begin(), winning_probabilites.end(), N_SIMULATIONS, this->size);
    }

    // Find maximum winning percentage
    int best_move_idx = argmax(winning_probabilites);

    // Set move according to simulation.
    player.addNode(viable_moves[best_move_idx]);
}