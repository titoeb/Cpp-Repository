#include "play_hex.h"

void play_hex(){
    int size;
    int player_O, player_X;
    bool selection = true;

    // Select the game size
    while(selection){
        selection = false;
        cout << "Welcome the game of hax." << endl;
        cout << "Please insert the size of the board. The size should be more than 1." << endl;
        cin >> size;

        if(size < 0) selection = true;
    }
    

    // Intro Players
    cout << "Please select the players to be one of: 0: RealHuman, 1: Random, 2: Monte Carlo" << endl;

    selection = true;
    while(selection){
        selection = false;
       
        // Select Player X
        cout << "Your Selection for player X:" << endl;
        cin >> player_X;

        if(!(player_X == 0 || player_X == 1 || player_X == 2)) selection = true;
    }

    selection = true;
    while(selection){
        selection = false;
       
        // Select Player O
        cout << "Your Selection for player O:" << endl;
        cin >> player_O;

        if(!(player_O == 0 || player_O == 1 || player_O == 2)) selection = true;
    }
    

    // Create the game
    Hex h(size, static_cast<PlayerType>(player_X), static_cast<PlayerType>(player_O));

    // Run the game
    while(true){
         // Let X take his turn and show the board to the user.
        h.player_X_turn();
        h.print();

        // Has X won?
        if(h.X_won()){
            cout << "Player X has won!" << endl;
            break;
        }

        // Let O take his turn and show the board to the user.
        h.player_O_turn();
        h.print();

        // Has O won?
        if(h.O_won()){
            cout << "Player 0 has won!" << endl;
            break;
        }
    }
}

void bot_play(){
    int size = 9;
    int player_O = 2;
    int player_X = 1;

    // Create the game
    Hex h(size, static_cast<PlayerType>(player_X), static_cast<PlayerType>(player_O));

    // Run the game
    while(true){
         // Let X take his turn and show the board to the user.
        h.player_X_turn();
        h.print();

        // Has X won?
        if(h.X_won()){
            cout << "Player X has won!" << endl;
            break;
        }

        // Let O take his turn and show the board to the user.
        h.player_O_turn();
        h.print();

        // Has O won?
        if(h.O_won()){
            cout << "Player 0 has won!" << endl;
            break;
        }
    }

}